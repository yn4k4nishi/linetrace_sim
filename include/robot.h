#include <vector>
#include <cmath>
#include <string>
#include "matplotlibcpp.h"
#include "motor.h"
#include "structs.h"

namespace plt = matplotlibcpp;

class Robot{
private:
    const std::string color = "black";
    const int sensor_num = 4;
    const double width = 0.1;
    //センサバーの位置(中心よりx前方，長さはy)
    const Position sensor_bar_pos = {0.05, 0.06};

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

    void plot_machine(){
        std::vector<double> x(6), y(6);
        for(int i = 0; i < 5; i++){
            x.at(i) = state.x + width * cos(state.theta + i * M_PI / 2.0) / 2.0;
            y.at(i) = state.y + width * sin(state.theta + i * M_PI / 2.0) / 2.0;
        }
        x.at(5) = state.x;
        y.at(5) = state.y;
        plt::plot(x, y, color);
        return;
    }

    void plot_sensor(){
        std::vector<double> x(2), y(2);
        x.at(0) = state.x + sensor_bar_pos.x * cos(state.theta) - sensor_bar_pos.y / 2 * sin(state.theta);
        y.at(0) = state.y + sensor_bar_pos.x * sin(state.theta) + sensor_bar_pos.y / 2 * cos(state.theta);
        x.at(1) = state.x + sensor_bar_pos.x * cos(state.theta) + sensor_bar_pos.y / 2 * sin(state.theta);
        y.at(1) = state.y + sensor_bar_pos.x * sin(state.theta) - sensor_bar_pos.y / 2 * cos(state.theta);
        plt::plot(x, y, color);
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
        plot_machine();
        plot_sensor();
        return;
    }
};