#include "videocamera.h"

#include <QCoreApplication>

VideoCamera::VideoCamera(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_centerx(0),
      m_centery(0),
      m_width(0),
      m_height(0),
      m_sampleArea(50),
      activateColorDetection(false),
      activatePidControl(false)
{
    /* I've move qRegisterMetaType< cv::Mat >("cv::Mat"); right before the QObject::connect call.
     * However I still have to 'F5' past the breakpoint in qglobal.h, it works afterwards.
       I might be wrong, but it seems that the location of qRegisterMetaType is not trivial. */
    // Per passare l'oggetto Mat tra gli eventi devo registrarlo
    qRegisterMetaType<Mat>("Mat");

    shower = new videocameraShower();
    // Create thread for get image from camera
    shower->moveToThread(&showerThread);
    // Eventi di videoshower
    connect(&timerCam, &QTimer::timeout, shower, &videocameraShower::readFrame);
    connect(shower, &videocameraShower::resultReady, this, &VideoCamera::updatePicture);
    connect(&showerThread, &QThread::finished, shower, &QObject::deleteLater);
    showerThread.start(QThread::TimeCriticalPriority);

    worker = new videocameraWorker();
    // Create thread for finding object
    worker->moveToThread(&workerThread);
    // Eventi di videoworker
    connect(worker, &videocameraWorker::objectFound, this, &VideoCamera::objectFound);
    //connect(worker, &videocameraWorker::contoursFound, this, &VideoCamera::updatePicture);
    //connect(shower, &videocameraShower::originalMat, worker, &videocameraWorker::retrieveOriginalMat);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread.start(QThread::HighestPriority);

    pid = new videocameraPid();
    // Create thread for finding object
    pid->moveToThread(&pidThread);
    // Eventi di pid
    //connect(pid, &videocameraPid::newPidOutput, this, &VideoCamera::onPidNewPosition);
    //connect(&timerMotor, &QTimer::timeout, pid, &videocameraPid::controlMotorLoop);
    connect(&pidThread, &QThread::finished, pid, &QObject::deleteLater);
    pidThread.start(QThread::HighPriority);

    timerCam.start(500);
    timerMotor.start(200);
}

void VideoCamera::onColorDetectionMode(bool activate)
{
    activateColorDetection = activate;
    if(activate) {
        connect(shower, &videocameraShower::originalMat, worker, &videocameraWorker::retrieveOriginalMat);
        connect(worker, &videocameraWorker::contoursFound, this, &VideoCamera::updatePicture);
        disconnect(shower, &videocameraShower::resultReady, this, &VideoCamera::updatePicture);
    }
    else {
        disconnect(shower, &videocameraShower::originalMat, worker, &videocameraWorker::retrieveOriginalMat);
        disconnect(worker, &videocameraWorker::contoursFound, this, &VideoCamera::updatePicture);
        connect(shower, &videocameraShower::resultReady, this, &VideoCamera::updatePicture);
    }

    qDebug()<< "color detection mode: " << activate;
}

void VideoCamera::onPidFollowMode(bool activate)
{
    activatePidControl = activate;
    if(activate) {
        connect(pid, &videocameraPid::newPidOutput, this, &VideoCamera::onPidNewPosition);
        connect(&timerMotor, &QTimer::timeout, pid, &videocameraPid::controlMotorLoop);
    }
    else {
        disconnect(pid, &videocameraPid::newPidOutput, this, &VideoCamera::onPidNewPosition);
        disconnect(&timerMotor, &QTimer::timeout, pid, &videocameraPid::controlMotorLoop);
    }

    qDebug()<< "pid detection mode: " << activate;
}

void VideoCamera::onColorPicked(QObject *event) {
    int minHue=255, minSaturation=255, minValue=255;
    int maxHue=0, maxSaturation=0, maxValue=0;
    for(int i=0;i<m_sampleArea;i++) {
        for(int j=0;j<m_sampleArea;j++) {
            int hue, saturation, value;
            int coordinateX = event->property("x").toInt() + i - m_sampleArea/2;
            int coordinateY = event->property("y").toInt() + j - m_sampleArea/2;
            QColor pixcolor = m_image.pixel(coordinateX, coordinateY);
            pixcolor.getHsv(&hue, &saturation, &value);
            // Hue
            minHue = min(minHue, hue);
            maxHue = max(maxHue, hue);
            // Saturation
            minSaturation = min(minSaturation, saturation);
            maxSaturation = max(maxSaturation, saturation);
            // Value
            minValue = min(minValue, value);
            maxValue = max(maxValue, value);
        }
    }

    vector<int> minHsv{minHue, minSaturation, minValue};
    vector<int> maxHsv{maxHue, maxSaturation, maxValue};
    worker->setMinColorPicked(minHsv);
    worker->setMaxColorPicked(maxHsv);

    qDebug()<<"New ColorPicked is: "<< minHsv << maxHsv;
}

void VideoCamera::onThresholdChanged(int thresholdInc) {
    int temp = worker->getThreshold();
    worker->setThreshold(qBound(10, temp + thresholdInc, 100));
    qDebug()<<"New Threshold is: "<<worker->getThreshold()<<" "<<thresholdInc;
}

void VideoCamera::onAreaChanged(int increment) {
    int temp = m_sampleArea + increment;
    m_sampleArea = qBound(10, temp, 200);
    qDebug()<<"New Area is: "<<m_sampleArea<<" "<<increment;
}

void VideoCamera::onMouseMoved(QObject *event) {
    m_mousex = event->property("x").toInt();
    m_mousey = event->property("y").toInt();

    //pid->setObjectCoordinate(m_mousex, m_mousey);
}

void VideoCamera::updatePicture(const QImage &image) {
    m_image = image;
    update();
}

void VideoCamera::objectFound(int centerx, int centery, int width, int height) {
    m_centerx = centerx;
    m_centery = centery;
    m_width = width;
    m_height = height;
    //qDebug()<<"Trovato centro: "<<m_centerx<<" "<<m_centery;

    if(activatePidControl)
        pid->setObjectCoordinate(m_centerx, m_centery);
}

void VideoCamera::onMotorsMoved(double positionX, double positionY)
{
    if(activatePidControl)
        pid->setCurrentMotorPosition(positionX, positionY);
}

void VideoCamera::onPidNewPosition(double outputX, double outputY)
{
    if(activatePidControl)
        emit moveMotors(outputX, outputY);
}

void VideoCamera::paint(QPainter *painter) {
     QPen pen;
     QRect imageRect(static_cast<int>(x()), static_cast<int>(y()), m_image.width(), m_image.height());
     painter->drawImage(imageRect, m_image);

     if(activateColorDetection)
     {
         //draw rect around mouse cursor
         pen.setColor(QColor("yellow"));
         pen.setWidth(3);
         painter->setPen(pen);
         painter->drawRect(m_mousex - m_sampleArea/2, m_mousey - m_sampleArea/2, m_sampleArea, m_sampleArea);
         // draw circle around object found
         if(m_width > 0) {
             pen.setColor(QColor("red"));
             pen.setWidth(3);
             painter->setPen(pen);
             painter->drawRect(m_centerx, m_centery, m_width, m_height);
         }
     }
}

VideoCamera::~VideoCamera() {
    timerCam.stop();
    timerMotor.stop();
    // bring object back to main thread
    //worker->moveToThread(QCoreApplication::instance()->thread());
    //shower->moveToThread(QCoreApplication::instance()->thread());
    //pid->moveToThread(QCoreApplication::instance()->thread());
    // kill all threads
    showerThread.quit();
    showerThread.wait();
    workerThread.quit();
    workerThread.wait();
    pidThread.quit();
    pidThread.wait();
}
