#ifndef LINETRACE_SIM_SENSOR_H
#define LINETRACE_SIM_SENSOR_H

#include <vector>
#include "structs.h"
#include "line.h"

class Sensor{
private:
    const double line_width = 0.019;
    const double visible_radius = 0.015;
    const int r_num = 10;
    const int theta_num = 20;

private:
    Position pos;
    std::vector<Line> lines;
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

    void setLines(std::vector<Line> lines){
        for(int i = 0; i < lines.size(); i++){
            this->lines.push_back(lines.at(i));
        }
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