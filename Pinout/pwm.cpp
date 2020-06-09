#include "pwm.h"

/*
 * PWM.cpp  Created on: 29 Apr 2015
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

#include "pwm.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <QDebug>

using namespace std;

namespace exploringRPi {

    PWM::PWM(QObject* parent) :
        QObject(parent),
        duty(DEFAULT_DUTY),
        period(DEFAULT_PERIOD),
        enable(DEFAULT_ENABLE)
    {}

    void PWM::init(int pinNumber) {
        this->number = pinNumber;
        ostringstream s;
        s << "pwm" << number;
        this->name = string(s.str());
        this->path = PWM_PATH + this->name + "/";
        this->analogFrequency = 100000;
        this->analogMax = 3.3;
        this->exportPWM();
    }

    int PWM::exportPWM() {
       return write(PWM_PATH, "export", this->number);
    }

    int PWM::unexportPWM() {
       return write(PWM_PATH, "unexport", this->number);
    }

    int PWM::setPeriod(unsigned int period_ns) {
        emit periodNsChanged(period_ns);
        return write(this->path, PWM_PERIOD, period_ns);
    }

    unsigned int PWM::getPeriod() {
        return atoi(read(this->path, PWM_PERIOD).c_str());
    }

    float PWM::period_nsToFrequency(unsigned int period_ns) {
        float period_s = (float)period_ns/1000000000;
        return 1.0f/period_s;
    }

    unsigned int PWM::frequencyToPeriod_ns(float frequency_hz) {
        float period_s = 1.0f/frequency_hz;
        return (unsigned int)(period_s*1000000000);
    }

    int PWM::setFrequency(float frequency_hz) {
        return this->setPeriod(this->frequencyToPeriod_ns(frequency_hz));
    }

    float PWM::getFrequency() {
        return this->period_nsToFrequency(this->getPeriod());
    }

    int PWM::setDutyCycleVal(unsigned int duty_ns) {
        float percentage = static_cast<float>(duty_ns)/this->period;
        emit dutyChanged(percentage);
        return write(this->path, PWM_DUTY, duty_ns);
    }

    int PWM::setDutyCyclePercentage(float percentage) {
        if ((percentage>100.0f)||(percentage<0.0f)) return -1;
        unsigned int period_ns = this->getPeriod();
        float duty_ns = period_ns * (percentage/100.0f);
        this->setDutyCycleVal((unsigned int) duty_ns );
        return 0;
    }

    unsigned int PWM::getDutyCycle() {
        return atoi(read(this->path, PWM_DUTY).c_str());
    }

    float PWM::getDutyCyclePercent() {
        unsigned int period_ns = this->getPeriod();
        unsigned int duty_ns = this->getDutyCycle();
        return 100.0f * (float)duty_ns/(float)period_ns;
    }

    int PWM::setPolarity(PWM::POLARITY polarity) {
        return write(this->path, PWM_POLARITY, polarity);
    }

    void PWM::invertPolarity() {
        if (this->getPolarity()==PWM::ACTIVE_LOW) this->setPolarity(PWM::ACTIVE_HIGH);
        else this->setPolarity(PWM::ACTIVE_LOW);
    }

    PWM::POLARITY PWM::getPolarity() {
        if (atoi(read(this->path, PWM_POLARITY).c_str())==0) return PWM::ACTIVE_LOW;
        else return PWM::ACTIVE_HIGH;
    }

    int PWM::calibrateAnalogMax(float analogMax) { //must be between 3.2 and 3.4
        if((analogMax<3.2f) || (analogMax>3.4f)) return -1;
        else this->analogMax = analogMax;
        return 0;
    }

    int PWM::analogWrite(float voltage) {
        if ((voltage<0.0f)||(voltage>3.3f)) return -1;
        this->setFrequency(this->analogFrequency);
        this->setPolarity(PWM::ACTIVE_LOW);
        this->setDutyCyclePercentage((100.0f*voltage)/this->analogMax);
        return this->run();
    }

    int PWM::run() {
        emit enableChanged(true);
        return write(this->path, PWM_RUN, 1);
    }

    bool PWM::isRunning() {
        string running = read(this->path, PWM_RUN);
        return (running=="1");
    }

    int PWM::stop() {
        emit enableChanged(false);
        return write(this->path, PWM_RUN, 0);
    }

    PWM::~PWM() {}

} /* namespace exploringRPi */
