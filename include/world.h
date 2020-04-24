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

    double time; //[s]
    double interval = 0.01; //[s]

    // パラメータ
    const double GOAL_TOLERANCE = 0.01; //[m]

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
        l2.end << 0.5,0.8;

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

        this->interval = robot.getInterval();
    }

    void update(){
        this->trajectory_x.push_back(this->getRobotState(robot).x);
        this->trajectory_y.push_back(this->getRobotState(robot).y);
        this->time += interval;
        this->robot->update();
    }

    void plot(){
        plt::clf();
        plt::axis("equal");

        for (auto &l : this->lines) {
            plt::plot(
                    std::vector<double>{l.start.x(),l.end.x()},
                    std::vector<double>{l.start.y(),l.end.y()},
                    {{"color","orange"}}
                    );
        }

        plt::plot(this->trajectory_x,this->trajectory_y);

        this->robot->plot();
        plotGoalFlag();

        plt::text(-0.25, 1.1, std::to_string(time) + "[s]");

        plt::xlim(-0.2,1.2);
        plt::ylim(-0.2,1.2);

        plt::pause(interval);
    }

    bool isFinished(){
        Eigen::Vector2d pos {this->getRobotState(robot).x, this->getRobotState(robot).y};

        if((this->lines.back().end - pos).norm() < GOAL_TOLERANCE){
            return true;
        }

        return false;
    }

private:
    State getRobotState(Robot *robot) {
        return robot->state;
    }

    void plotGoalFlag(){

        plt::fill<double>(
                {this->lines.back().end.x(), this->lines.back().end.x() + 0.07, this->lines.back().end.x() + 0.07,this->lines.back().end.x()},
                {this->lines.back().end.y() + 0.05, this->lines.back().end.y() + 0.05, this->lines.back().end.y() + 0.1,this->lines.back().end.y() + 0.1},
                {}
        );

        plt::plot({this->lines.back().end.x(),this->lines.back().end.x()},
                  {this->lines.back().end.y(),this->lines.back().end.y() + 0.1},
                  {{"color","k"}});
    }
};

#endif //LINETRACE_SIM_WORLD_H
