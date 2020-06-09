#include "videocamerapid.h"
#include <QDebug>

videocameraPid::videocameraPid(QObject* parent) :
    QObject(parent),
    minipidX(parent, 0.02, 0.005, 0, 0),
    minipidY(parent, 0.02, 0.005, 0,0),
    directionSearchX(RIGHT),
    directionSearchY(UP)
{
    minipidX.setMaxIOutput(0.2);
    minipidX.setOutputLimits(-0.05, 0.05);
    minipidY.setMaxIOutput(0.2);
    minipidY.setOutputLimits(-0.05, 0.05);

    minipidX.setSetpoint(PICTURE_WIDTH/2);
    minipidY.setSetpoint(PICTURE_HEIGHT/2);
}

videocameraPid::~videocameraPid()
{

}

void videocameraPid::controlMotorLoop()
{
    if((objectX>0) & (objectY>0))
    {
        double outputX = minipidX.getOutput(objectX);
        double outputY = minipidY.getOutput(objectY);
        qDebug() << "Setpoint X is: 250, actualPoint is: " << objectX;
        qDebug() << "Calculated X output is: " << outputX;
        //qDebug() << "Setpoint Y is: 200, actualPoint is: " << objectY;
        //qDebug() << "Calculated Y output is: " << outputY;

        emit newPidOutput(outputX, -outputY);
    }
    else
    {
        double incY = 0;
        double incX = 0;

        if((currentPositionY > 6.1) & (directionSearchY==DOWN))
            directionSearchY = UP;
         else if((currentPositionY < 2.9) & (directionSearchY==UP))
            directionSearchY = DOWN;

        if((currentPositionX > 6.1) & (directionSearchX==RIGHT))
        {
            directionSearchX=LEFT;
            incY = (directionSearchY == DOWN) ? 0.5 : -0.5;
        }
        else if((currentPositionX < 2.9) & (directionSearchX==LEFT))
        {
            directionSearchX=RIGHT;
            incY = (directionSearchY == DOWN) ? 0.5 : -0.5;
        }

        incX = (directionSearchX == RIGHT) ? 0.1 : -0.1;

        //qDebug()<<"PositionX: "<<currentPositionX<<","<<directionSearchX;
        //qDebug()<<"PositionY: "<<currentPositionY<<","<<directionSearchY;

        emit newPidOutput(incX, incY);
    }
}

void videocameraPid::setCurrentMotorPosition(double positionX, double positionY)
{
    currentPositionX = positionX;
    currentPositionY = positionY;
}

void videocameraPid::setObjectCoordinate(int x, int y)
{
    objectX=x;
    objectY=y;
}
