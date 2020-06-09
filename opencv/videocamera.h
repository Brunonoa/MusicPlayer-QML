#ifndef VIDEOCAMERA_H
#define VIDEOCAMERA_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "opencv_global.h"
#include "videocamerashower.h"
#include "videocameraworker.h"
#include "videocamerapid.h"

class OPENCV_EXPORT VideoCamera : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit VideoCamera(QQuickItem *parent = nullptr);
    ~VideoCamera() override;

    void paint(QPainter *painter) override;

private:
    void init();

signals:
    void moveMotors(double outputX, double outputY);

public slots:
    void updatePicture(const QImage&);
    void objectFound(int centerx, int centery, int width, int heigth);
    // Slots for color detectionMode
    void onColorDetectionMode(bool activate);
    void onAreaChanged(int increment);
    void onColorPicked(QObject *event);
    void onThresholdChanged(int threshold);
    void onMouseMoved(QObject *event);
    // Slots for motor control
    void onPidFollowMode(bool activate);
    void onPidNewPosition(double outputX, double outputY);
    void onMotorsMoved(double positionX, double positionY);

private:
    // Threads
    videocameraShower* shower;
    videocameraWorker* worker;
    videocameraPid* pid;
    // Coordinate oggetto trovato
    int m_centerx, m_centery, m_width, m_height;
    // Coordinate mouse
    int m_mousex, m_mousey, m_sampleArea;
    // Controllo logica
    bool activateColorDetection;
    bool activatePidControl;
    QImage m_image;
    QThread showerThread, workerThread, pidThread;
    QTimer timerCam, timerMotor;
};

#endif // VIDEOCAMERA_H

