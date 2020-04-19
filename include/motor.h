class Motor{
private:
    double duty;
    double speed;
    double acceleration;

public:
    Motor(){
    }

private:
    void update(){
        speed = duty;
    }

public:
    void setDuty(double duty){
        duty = this->duty;
        return;
    }
    double getSpeed(){
        return speed;
    }
};