#include <cmath>

class Motor{
private:
    //巻線抵抗
    const double resistance = 0.299;
    //インダクタンス
    const double inductance = 8.2e-5;
    //トルク定数=逆起電力係数
    const double torque_constant = 3.02e-2;
    //慣性モーメント
    const double inertia = 1.42e-5;
    //動粘性系数
    const double viscous_friction_constant = 3.04e-3;

    //電源電圧
    const double voltage = 24.0;
    //車輪半径
    const double tire_radius = 0.05;

private:
    double interval;
    double duty;
    double current;
    double angular_velocity;
    double speed;

public:
    Motor(double interval):
            interval(interval),
            duty(0.0),
            speed(0.0),
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
        double k1_i = didt(current, angular_velocity);
        double k1_w = dwdt(current, angular_velocity);
        double k2_i = didt(current + interval * k1_i / 2, angular_velocity + interval * k1_w / 2);
        double k2_w = dwdt(current + interval * k1_i / 2, angular_velocity + interval * k1_w / 2);
        double k3_i = didt(current + interval * k2_i / 2, angular_velocity + interval * k2_w / 2);
        double k3_w = dwdt(current + interval * k2_i / 2, angular_velocity + interval * k2_w / 2);
        double k4_i = didt(current + interval * k3_i, angular_velocity + interval * k3_w);
        double k4_w = dwdt(current + interval * k3_i, angular_velocity + interval * k3_w);
        current += interval * (k1_i + 2 * k2_i + 2 * k3_i + k4_i) / 6;
        angular_velocity += interval * (k1_w + 2 * k2_w + 2 * k3_w + k4_w) / 6;
        speed = 2.0 * M_PI * angular_velocity * tire_radius;
        return;
    }

    void setDuty(double duty){
        this->duty = duty;
        return;
    }

    double getSpeed(){
        return speed;
    }
};