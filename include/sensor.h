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
    std::vector<Position> observation_points;
    double value;

public:
    Sensor():
            pos({0.0, 0.0}),
            observation_points(r_num * theta_num),
            value(0.0){
    }

private:
    void updateObservationPoint(){
        for(int i = 0; i < theta_num; i++){
            double theta = 2.0 * M_PI * i / theta_num;
            for(int j = 0; j < r_num; j++){
                double r = visible_radius * j / r_num;

                observation_points.at(i * r_num + j).x = pos.x + r * cos(theta);
                observation_points.at(i * r_num + j).y = pos.y + r * sin(theta);
            }
        }
        return;
    }

public:
    void update(){
            updateObservationPoint();
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