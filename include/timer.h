//
// Created by ynakanishi on 2020/04/19.
//

#ifndef LINETRACE_SIM_TIMER_H
#define LINETRACE_SIM_TIMER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>

class Timer{
    unsigned int interval_ms;//[milliseconds]
    std::vector<std::function<void(void)>> funcs;

    bool isRunning = false;

public:
    Timer(unsigned int interval_ms = 100):interval_ms(interval_ms){}
    ~Timer(){}

    void bind(std::function<void(void)> func){
        this->funcs.push_back(func);
    }

    void start(){
        this->isRunning = true;

        std::thread([this](){
            while (isRunning){
                for (auto &f : this->funcs) {
                    f();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
            }
        }).detach();
    }

    void stop(){
        this->isRunning = false;
    }

};

#endif //LINETRACE_SIM_TIMER_H
