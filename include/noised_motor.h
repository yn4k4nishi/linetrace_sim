#ifndef LINETRACE_SIM_NOISED_MOTOR_H
#define LINETRACE_SIM_NOISED_MOTOR_H

#include <random>
#include "motor.h"

class NoisedMotor : public Motor{
private:
    std::random_device seed;
    std::default_random_engine engine;
    std::normal_distribution<> dist;

public:
    NoisedMotor(double interval):
            Motor(interval),
            engine(seed()),
            dist(1.0, 0.4){
    }

public:
    double getSpeed(){
        return angular_velocity / gear_ratio * tire_radius * dist(engine);
    }
};

#endif