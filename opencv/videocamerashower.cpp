#include "videocamerashower.h"

videocameraShower::videocameraShower() :
    cap(VideoCapture(0))
{
    qDebug()<<"Camera opened";
}

videocameraShower::~videocameraShower()
{
    qDebug()<<"Camera closed";
    cap.release();
}

void videocameraShower::readFrame()
{
    if(cap.isOpened())
    {
        Mat cam_image;
        t0 = getTickCount();
        cap >> cam_image;
        // Show the colored image
        cvtColor(cam_image, original_image, CV_BGR2RGB);
        emit originalMat(original_image);

        // Pass the camera frame for conversion to QImage
        m_image = QImage(static_cast<uchar*>(original_image.data), original_image.cols, original_image.rows,
                         static_cast<int>(original_image.step), QImage::Format_RGB888);

        //qDebug() << "Frame rate = " << getTickFrequency() / (getTickCount() - t0);
        emit resultReady(m_image);
    }
}

