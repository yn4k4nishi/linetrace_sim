#include "world.h"
#include "timer.h"

void say_hello(){
    std::cout << "hello" << std::endl;
}

int main(){

    Timer timer;
    timer.bind(say_hello);

    timer.start();

    while (true){

    }

//    Robot robot;
//
//    World world;
//    world.setLines();
//    world.setRobot(robot);
//
//    while (!world.isFinished()){
////        world.update();
//        world.plot();
//    }

    return 0;
}
