class Motor{
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
        duty = this->duty;
        return;
    }
    double getSpeed(){
        return speed;
    }
};