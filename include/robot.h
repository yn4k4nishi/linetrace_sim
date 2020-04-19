#include <vector>
#include <cmath>
#include "motor.h"

struct State{
    double x;
    double y;
    double theta;
};

class Robot{
private:
    const int sensor_num = 4;
    const double width = 0.1;

private:
    double interval;
    State robot_state;
    Motor motor_r, motor_l;
    std::vector<double> sensor_value;

public:
    Robot(double interval = 0.01, State robot_state = {0.0, 0.0, 0.0}) :
            interval(interval),
            robot_state(robot_state),
            sensor_value(sensor_num){
    }

private:
    void update_state(){
        double speed_r = motor_r.getSpeed();
        double speed_l = motor_l.getSpeed();

        double v = (speed_r + speed_l) / 2.0;
        double omega = (speed_r - speed_l) / width;

        robot_state.x += v * interval * cos(robot_state.theta + omega * interval / 2.0);
        robot_state.y += v * interval * sin(robot_state.theta + omega * interval / 2.0);
        robot_state.theta += omega * interval;
        return;
    }

public:
    void update(){
        motor_r.update();
        motor_l.update();
        update_state();
        return;
    }

    void setDuty(double right, double left){
        motor_r.setDuty(right);
        motor_l.setDuty(left);
        return;
    }

    State getState(){
        return robot_state;
    }

    std::vector<double> getSensorData(){
        return sensor_value;
    }
};