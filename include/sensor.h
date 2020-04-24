#ifndef LINETRACE_SIM_SENSOR_H
#define LINETRACE_SIM_SENSOR_H

#include <vector>
#include <Eigen/Core>
#include "structs.h"
#include "line.h"

class Sensor{
protected:
    const double line_width = 0.019;
    const double visible_radius = 0.015;
    const int r_num = 10;
    const int theta_num = 20;

protected:
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

    void updateValue(){
        int number_of_on_line = 0;

        for(int i = 0; i < r_num * theta_num; i++){
            bool is_on_line = false;

            for(int j = 0; j < lines.size(); j++){
                Eigen::Vector2d a, b;
                //startから観測点のベクトル
                a << observation_points.at(i).x - lines.at(j).start.x(), observation_points.at(i).y - lines.at(j).start.y();
                //startからendのベクトル
                b << lines.at(j).end.x() - lines.at(j).start.x(), lines.at(j).end.y() - lines.at(j).start.y();

                double distance;
                if(a.dot(b) < 0){
                    distance = a.norm();
                }else if(a.dot(b) / b.norm() < b.norm()){
                    distance = abs(a.x() * b.y() - a.y() * b.x()) / b.norm();
                }else{
                    Eigen::Vector2d c;
                    //endから観測点のベクトル
                    c << observation_points.at(i).x - lines.at(j).end.x(), observation_points.at(i).y - lines.at(j).end.y();
                    distance = c.norm();
                }

                if(distance < line_width / 2){
                    number_of_on_line++;
                    break;
                }
            }
        }
        value = (double)number_of_on_line / (r_num * theta_num);
        return;
    }

public:
    void update(){
            updateObservationPoint();
            updateValue();
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