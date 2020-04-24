#include "world.h"

/*
 * Agentクラス
 */

class Agent{
    Robot *robot;

public:
    Agent(){}
    ~Agent(){}

    void rideRobot(Robot &robot){
        this->robot = &robot;
    }

    // ロボットを操縦する関数
    void steerRobot(){
        auto sensor_data = robot->getSensorData();

        std::cout << sensor_data[0] << "\t";
        std::cout << sensor_data[1] << "\t";
        std::cout << sensor_data[2] << "\t";
        std::cout << sensor_data[3] << std::endl;

        if(sensor_data[0] > 0){
            robot->setDuty(0,0.5);
        } else if(sensor_data[3] > 0){
            robot->setDuty(0.5,0);
        } else {
            robot->setDuty(0.5,0.5);
        }

    }
};

/*
 * main
 */
int main(){

    Robot robot(0.01,{0,0,M_PI_4});

    Agent agent;
    agent.rideRobot(robot);

    World world;
    world.setLines();
    world.setRobot(robot);

    while (!world.isFinished()){
        agent.steerRobot();

        world.update();
        world.plot();
    }

    plt::show();

    return 0;
}
