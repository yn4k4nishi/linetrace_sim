#ifndef LINETRACE_SIM_SENSOR_H
#define LINETRACE_SIM_SENSOR_H

#include "structs.h"

class Sensor{
private:
    Position pos;
    double value;

public:
    Sensor():
            pos({0.0, 0.0}),
            value(0.0){
    }

public:
    void update(){
        return;
    }

    void setPosition(Position pos){
        this->pos = pos;
        return;
    }

    double getValue(){
        return value;
    }
};

#endif