#ifndef VIDEOCAMERAPID_H
#define VIDEOCAMERAPID_H

#include <QObject>
#include <QTimer>

#include "minipid.h"

#include "opencv_global.h"

#define PICTURE_WIDTH   500
#define PICTURE_HEIGHT  400

class OPENCV_EXPORT videocameraPid : public QObject
{
    Q_OBJECT
public:
    Q_ENUMS(DirectionX)
    Q_ENUMS(DirectionY)
    enum DirectionX { RIGHT=0, LEFT };
    enum DirectionY {UP=0, DOWN};

    videocameraPid(QObject* parent = nullptr);
    ~videocameraPid() override;
    void setObjectCoordinate(int x, int y);
    void setCurrentMotorPosition(double positionX, double positionY);

    void controlMotorLoop();

signals:
    void newPidOutput(double outputX, double outputY);

private:
    MiniPID minipidX, minipidY;
    // Posizione dell'oggetto
    double objectX, objectY;
    // Posizione dei motori
    double currentPositionX, currentPositionY;

    DirectionX directionSearchX;
    DirectionY directionSearchY;
    QTimer timer;
};

#endif // VIDEOCAMERAPID_H
