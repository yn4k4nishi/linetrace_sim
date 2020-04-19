#include <vector>
#include "motor.h"

struct State{
    double x;
    double y;
    double theta;
};

class Robot{
private:
    State robot_state;
    Motor motor_r, motor_l;
    int sensor_num;
    std::vector<double> sensor_value;

public:
    Robot(State robot_state = {0.0, 0.0, 0.0}, int sensor_num = 4) :
            robot_state(this->robot_state),
            sensor_num(this->sensor_num),
            sensor_value(sensor_num){
    }

private:
    void update_state(){
        motor_r.getSpeed();
        motor_l.getSpeed();
        return;
    }

public:
    void update(){
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