#ifndef LINETRACE_SIM_NOISED_MOTOR_H
#define LINETRACE_SIM_NOISED_MOTOR_H

#include "motor.h"

class NoisedMotor : public Motor{
public:
    NoisedMotor(double interval):
            Motor(interval){
    }

public:
    double getSpeed(){
        return angular_velocity / gear_ratio * tire_radius;
    }
};

#endif