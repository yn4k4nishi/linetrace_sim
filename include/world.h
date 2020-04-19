//
// Created by ynakanishi on 2020/04/19.
//

#ifndef LINETRACE_SIM_WORLD_H
#define LINETRACE_SIM_WORLD_H

#include <iostream>
#include <vector>
#include "line.h"
#include "matplotlibcpp.h"
#include "robot.h"

namespace plt = matplotlibcpp;

class World{
    std::vector<Line> lines;
    Robot *robot;

    // プロット用のvector
    std::vector<double> course_x,course_y;
    std::vector<double> trajectory_x,trajectory_y;

public:
    World(){}
    ~World(){}

    void setLines(){
        // todo コースのファイル読み込み
        Line l1,l2,l3;
        l1.start << 0,0;
        l1.end << 2,1;

        l2.start = l1.end;
        l2.end << 2,4;

        l3.start = l2.end;
        l3.end << 5,5;

        this->lines.clear();

        this->lines.push_back(l1);
        this->lines.push_back(l2);
        this->lines.push_back(l3);

        //// plot用
        this->course_x.clear();
        this->course_y.clear();

        this->course_x.push_back(this->lines.front().start.x());
        this->course_y.push_back(this->lines.front().start.y());

        for (auto &l : this->lines) {
            this->course_x.push_back(l.end.x());
            this->course_y.push_back(l.end.y());
        }
    }

    void setRobot(Robot &robot){
        this->robot = &robot;
    }

    void update(){
        this->robot->update();
        this->trajectory_x.push_back(this->robot->getState().x);
        this->trajectory_y.push_back(this->robot->getState().y);
    }

    void plot(){
        plt::plot(this->course_x, this->course_y);
        plt::show();
    }
};

#endif //LINETRACE_SIM_WORLD_H
