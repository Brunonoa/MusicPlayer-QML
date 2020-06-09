#ifndef MINIPID_H
#define MINIPID_H

#include <QObject>

class MiniPID : public QObject
{
    Q_OBJECT
public:
    explicit MiniPID(QObject *parent = nullptr, double p = 0, double i = 0, double d = 0);
    explicit MiniPID(QObject *parent = nullptr, double p = 0, double i = 0, double d = 0, double f = 0);

    void setP(double);
    void setI(double);
    void setD(double);
    void setF(double);
    void setPID(double, double, double);
    void setPID(double, double, double, double);
    void setMaxIOutput(double);
    void setOutputLimits(double);
    void setOutputLimits(double,double);
    void setDirection(bool);
    void setSetpoint(double);
    void reset();
    void setOutputRampRate(double);
    void setSetpointRange(double);
    void setOutputFilter(double);
    double getOutput();
    double getOutput(double);
    double getOutput(double, double);

signals:

public slots:

private:
    double clamp(double, double, double);
    bool bounded(double, double, double);
    void checkSigns();
    void init();
    double P;
    double I;
    double D;
    double F;

    double maxIOutput;
    double maxError;
    double errorSum;

    double maxOutput;
    double minOutput;

    double setpoint;

    double lastActual;

    bool firstRun;
    bool reversed;

    double outputRampRate;
    double lastOutput;

    double outputFilter;

    double setpointRange;
};

#endif // MINIPID_H
