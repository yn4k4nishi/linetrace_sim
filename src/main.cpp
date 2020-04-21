#include "world.h"

int main(){

    Robot robot;

    robot.setDuty(1,0.5);

    World world;
    world.setLines();
    world.setRobot(robot);

    while (!world.isFinished()){
        world.update();
        world.plot();
    }

    return 0;
}
