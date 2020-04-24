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
    const double GOAL_TOLERANCE = 0.1; //[m]
    const double FIELD_SIZE = 1.0; //[m]

public:
    World():
            time(0.0){
        plt::figure_size(1200,1200);
    }
    ~World(){}

    void setLines(){
        // todo コースのファイル読み込み
        Line l1,l2,l3;
        l1.start << 0.1,0.1;
        l1.end << 0.4,0.2;

        l2.start = l1.end;
        l2.end << 0.5,0.8;

        l3.start = l2.end;
        l3.end << 0.9,0.9;

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
        plt::suptitle("time : " + std::to_string(time) + "[s]");

        plt::subplot(1,2,1);
        plt::axis("equal");

        // 範囲のプロット
        plt::plot({0,FIELD_SIZE,FIELD_SIZE,0,0},
                  {0,0,FIELD_SIZE,FIELD_SIZE,0},
                  {{"alpha","0.6"},{"color","red"}});

        //ラインのプロット
        for (auto &l : this->lines) {
            plt::plot(
                    std::vector<double>{l.start.x(),l.end.x()},
                    std::vector<double>{l.start.y(),l.end.y()},
                    {{"color","orange"}}
                    );
        }

        //軌跡のプロット
        plt::plot(this->trajectory_x,this->trajectory_y);

        plotGoalFlag();
        this->robot->plot();

        plt::xlim(-0.2,FIELD_SIZE + 0.2);
        plt::ylim(-0.2,FIELD_SIZE + 0.2);

        // センサ値のプロット
        plt::subplot(1,2,2);
        auto data = this->robot->getSensorData();
        plt::ylim(0,1);
        plt::bar(data);

        plt::pause(interval);
    }

    bool isFinished(){
        Eigen::Vector2d pos {this->getRobotState(robot).x, this->getRobotState(robot).y};

        if((this->lines.back().end - pos).norm() < GOAL_TOLERANCE){
            return true;
        }

        if( 0.0 > getRobotState(robot).x || getRobotState(robot).x > FIELD_SIZE ){
            return true;
        }
        if( 0.0 > getRobotState(robot).y || getRobotState(robot).y > FIELD_SIZE ){
            return true;
        }

        return false;
    }

    double getTime(){
        return this->time;
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
