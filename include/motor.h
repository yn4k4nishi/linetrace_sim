class Motor{
private:
    const double resistance = 0.299;
    const double inductance = 0.082e-3;
    const double torque_constant = 30.2e3;
    const double inertia = 142.0e-7;
    const double viscous_friction_constant = 3.04e-3;

    const double voltage = 24.0;

private:
    double duty;
    double speed;
    double acceleration;

public:
    Motor(){
    }

public:
    void update(){
        speed = duty;
    }

    void setDuty(double duty){
        this->duty = duty;
        return;
    }
    double getSpeed(){
        return speed;
    }
};