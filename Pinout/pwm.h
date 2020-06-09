#ifndef PWM_H
#define PWM_H

/*
 * PWM.h  Created on: 29 Apr 2015
 * Copyright (c) 2015 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring Raspberry Pi"
 * See: www.exploringrpi.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European
 * Union Public License (the "EUPL") version 1.1 as published by the
 * European Union. Any use of this Software, other than as authorized
 * under this License is strictly prohibited (to the extent such use
 * is covered by a right of the copyright holder of this Software).
 *
 * This Software is provided under the License on an "AS IS" basis and
 * without warranties of any kind concerning the Software, including
 * without limitation merchantability, fitness for a particular purpose,
 * absence of defects or errors, accuracy, and non-infringement of
 * intellectual property rights other than copyright. This disclaimer
 * of warranty is an essential part of the License and a condition for
 * the grant of any rights to this Software.
 *
 * For more details, see http://www.derekmolloy.ie/
 */

#include <QObject>
#include <string>
using std::string;

#define PWM_PATH        "/sys/class/pwm/pwmchip0/"
#define PWM_PERIOD      "period"
#define PWM_DUTY        "duty_cycle"
#define PWM_POLARITY    "polarity"
#define PWM_RUN         "enable"

#define DEFAULT_PERIOD  20000000
#define DEFAULT_DUTY    560000
#define DEFAULT_ENABLE  false

namespace exploringRPi {

/**
 * @class PWM
 * @brief A class to control a basic PWM output -- you must know the exact sysfs filename
 * for the PWM output.
 */
class PWM : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(float duty READ getDuty WRITE setDuty NOTIFY dutyChanged)
    Q_PROPERTY(unsigned int period READ getPeriodNs WRITE setPeriodNs NOTIFY periodNsChanged)
    Q_PROPERTY(bool enable READ getEnable WRITE setEnable NOTIFY enableChanged)

    enum POLARITY{ ACTIVE_LOW=0, ACTIVE_HIGH=1 };

    float duty;
    unsigned int period;
    bool enable;

signals:
    void dutyChanged(float duty);
    void periodNsChanged(unsigned int period);
    void enableChanged(bool enable);

private:
    int number;
    string name;
    string path;
    float analogFrequency;  //defaults to 100,000 Hz
    float analogMax;        //defaults to 3.3V

public:
    PWM(QObject* parent = nullptr);

    Q_INVOKABLE void init(int pinNumber);

    float getDuty() {return duty;}
    void setDuty(float dutyVal) {duty=dutyVal; setDutyCyclePercentage(dutyVal);}

    unsigned int getPeriodNs() {return period;}
    void setPeriodNs(unsigned int periodNs) {period=periodNs; setPeriod(periodNs);}

    bool getEnable() {return enable;}
    void setEnable(bool enableVal) {enable=enableVal; enableVal ? run() : stop();}

    virtual int setPeriod(unsigned int period_ns);
    virtual unsigned int getPeriod();
    virtual int setFrequency(float frequency_hz);
    virtual float getFrequency();
    virtual int setDutyCycleVal(unsigned int duration_ns);
    virtual int setDutyCyclePercentage(float percentage);
    virtual unsigned int getDutyCycle();
    virtual float getDutyCyclePercent();

    virtual int setPolarity(PWM::POLARITY);
    virtual void invertPolarity();
    virtual PWM::POLARITY getPolarity();

    virtual void setAnalogFrequency(float frequency_hz) { this->analogFrequency = frequency_hz; }
    virtual int calibrateAnalogMax(float analogMax); //must be between 3.2 and 3.4
    virtual int analogWrite(float voltage);

    virtual int run();
    virtual bool isRunning();
    virtual int stop();

    virtual ~PWM();

private:
    float period_nsToFrequency(unsigned int);
    unsigned int frequencyToPeriod_ns(float);
    int unexportPWM();
    int exportPWM();
};

} /* namespace exploringRPi */

#endif // PWM_H
