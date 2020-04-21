#ifndef LINETRACE_SIM_NOISED_MOTOR_H
#define LINETRACE_SIM_NOISED_MOTOR_H

#include <random>
#include "motor.h"

class NoisedMotor : public Motor{
private:
    const double noise_dev = 0.4;
    const double bias_dev = 0.2;
    
private:
    std::random_device seed;
    std::default_random_engine engine;
    std::normal_distribution<> noise_dist, bias_dist;
    double bias;

public:
    NoisedMotor(double interval):
            Motor(interval),
            engine(seed()),
            noise_dist(1.0, noise_dev),
            bias_dist(1.0, bias_dev),
            bias(bias_dist(engine)){
    }

public:
    double getSpeed(){
        return angular_velocity / gear_ratio * tire_radius * noise_dist(engine) * bias;
    }
};

#endif