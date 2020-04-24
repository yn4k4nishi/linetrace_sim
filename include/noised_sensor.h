#ifndef LINETRACE_SIM_NOISED_SENSOR_H
#define LINETRACE_SIM_NOISED_SENSOR_H

#include <random>
#include "sensor.h"

class NoisedSensor : public Sensor{
private:
    const double noise_dev = 0.1;

private:
    std::random_device seed;
    std::default_random_engine engine;
    std::normal_distribution<> noise_dist;

public:
    NoisedSensor():
            engine(seed()),
            noise_dist(0.0, noise_dev){
    }

public:
    double getValue(){
        double v = value + noise_dist(engine);
        if(v > 1.0){
            v = 1.0;
        }else if(v < 0.0){
            v = 0.0;
        }
        return v;
    }

};

#endif