//
// Created by ynakanishi on 2020/04/19.
//

#ifndef LINETRACE_SIM_WORLD_H
#define LINETRACE_SIM_WORLD_H

#include <iostream>
#include <vector>
#include <string>
#include "line.h"
#include "matplotlibcpp.h"
#include "robot.h"

namespace plt = matplotlibcpp;

class World{
    std::vector<Line> lines;
    Robot *robot;

    // プロット用のvector
    std::vector<double> trajectory_x,trajectory_y;

    // パラメータ
    const double GOAL_TOLERANCE = 0.01;// [m]

    double time;

public:
    World():
            time(0.0){}
    ~World(){}

    void setLines(){
        // todo コースのファイル読み込み
        Line l1,l2,l3;
        l1.start << 0,0;
        l1.end << 0.4,0.2;

        l2.start = l1.end;
        l2.end << 0.1,0.8;

        l3.start = l2.end;
        l3.end << 1,1;

        this->lines.clear();

        this->lines.push_back(l1);
        this->lines.push_back(l2);
        this->lines.push_back(l3);
    }

    void setRobot(Robot &robot){
        this->robot = &robot;
        this->robot->setLines(this->lines);
    }

    void update(){
        this->trajectory_x.push_back(this->getRobotState(robot).x);
        this->trajectory_y.push_back(this->getRobotState(robot).y);
        this->time += 0.01;
        this->robot->update();
    }

    void plot(){
        plt::clf();
        plt::axis("equal");

        for (auto &l : this->lines) {
            plt::plot(
                    std::vector<double>{l.start.x(),l.end.x()},
                    std::vector<double>{l.start.y(),l.end.y()},
                    {{"color","b"}}
                    );
        }

        plt::plot(this->trajectory_x,this->trajectory_y);

        this->robot->plot();

        plt::text(-0.25, 1.1, std::to_string(time));

        plt::xlim(-0.2,1.2);
        plt::ylim(-0.2,1.2);

        plt::pause(0.01);
    }

    bool isFinished(){
        // todo : 実装
        Eigen::Vector2d pos {this->getRobotState(robot).x, this->getRobotState(robot).y};

//        if((this->lines.end()->end - pos).norm() < GOAL_TOLERANCE){
//            return true;
//        }

        return false;
    }

private:
    State getRobotState(Robot *robot) {
        return robot->state;
    }
};

#endif //LINETRACE_SIM_WORLD_H
