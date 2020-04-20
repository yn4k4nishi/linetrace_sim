#include <vector>
#include <cmath>
#include "matplotlibcpp.h"
#include "motor.h"
#include "structs.h"

namespace plt = matplotlibcpp;

class Robot{
private:
    const int sensor_num = 4;
    const double width = 0.1;

private:
    double interval;
    State state;
    Motor motor_r, motor_l;
    std::vector<double> sensor_value;

public:
    Robot(double interval = 0.01, State initial_state = {0.0, 0.0, 0.0}) :
            interval(interval),
            state(initial_state),
            sensor_value(sensor_num),
            motor_r(interval),
            motor_l(interval){
    }

private:
    void update_state(){
        double speed_r = motor_r.getSpeed();
        double speed_l = motor_l.getSpeed();

        double v = (speed_r + speed_l) / 2.0;
        double omega = (speed_r - speed_l) / width;

        state.x += v * interval * cos(state.theta + omega * interval / 2.0);
        state.y += v * interval * sin(state.theta + omega * interval / 2.0);
        state.theta += omega * interval;
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
        return state;
    }

    std::vector<double> getSensorData(){
        return sensor_value;
    }

    void plot(){
        std::vector<double> x(6), y(6);
        for(int i = 0; i < 5; i++){
            x.at(i) = state.x + width * cos(state.theta + i * M_PI / 2.0) / 2.0;
            y.at(i) = state.y + width * sin(state.theta + i * M_PI / 2.0) / 2.0;
        }
        x.at(5) = state.x;
        y.at(5) = state.y;

        plt::plot(x, y);
        return;
    }
};