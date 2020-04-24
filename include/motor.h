#ifndef LINETRACE_SIM_MOTOR_H
#define LINETRACE_SIM_MOTOR_H

#include <cmath>

class Motor{
protected:
    //巻線抵抗
    const double resistance = 5.55;
    //インダクタンス
    const double inductance = 0.046e-3;
    //トルク定数=逆起電力係数
    const double torque_constant = 2.14e-3;
    //慣性モーメント
    const double inertia = 0.066e-7;
    //動粘性系数
    const double viscous_friction_constant = inertia / 7.97e-3;

    //電源電圧
    const double voltage = 2.4;
    //ギア比
    const double gear_ratio = 12.7;
    //車輪半径
    const double tire_radius = 0.05;

protected:
    double interval;
    double duty;
    double current;
    double angular_velocity;

public:
    Motor(double interval):
            interval(interval),
            duty(0.0),
            angular_velocity(0.0),
            current(0.0){
    }

private:
    double didt(double i, double w){
        return (duty * voltage - resistance * i - torque_constant * w) / inductance;
    }

    double dwdt(double i, double w){
        return (torque_constant * i - viscous_friction_constant * w) / inertia;
    }

public:
    void update(){
        double dt = interval / 1000;
        for(int i = 0; i < 1000; i++){
            double k1_i = didt(current, angular_velocity);
            double k1_w = dwdt(current, angular_velocity);
            double k2_i = didt(current + dt * k1_i / 2, angular_velocity + dt * k1_w / 2);
            double k2_w = dwdt(current + dt * k1_i / 2, angular_velocity + dt * k1_w / 2);
            double k3_i = didt(current + dt * k2_i / 2, angular_velocity + dt * k2_w / 2);
            double k3_w = dwdt(current + dt * k2_i / 2, angular_velocity + dt * k2_w / 2);
            double k4_i = didt(current + dt * k3_i, angular_velocity + dt * k3_w);
            double k4_w = dwdt(current + dt * k3_i, angular_velocity + dt * k3_w);
            current += dt * (k1_i + 2 * k2_i + 2 * k3_i + k4_i) / 6;
            angular_velocity += dt * (k1_w + 2 * k2_w + 2 * k3_w + k4_w) / 6;
        }
        return;
    }

    void setDuty(double duty){
        if(duty < -1.0){
            duty = -1.0;
        }else if(duty > 1.0){
            duty = 1.0;
        }
        this->duty = duty;
        return;
    }

    double getSpeed(){
        return angular_velocity / gear_ratio * tire_radius;
    }

    double getCurrent(){
        return current;
    }
};

#endif