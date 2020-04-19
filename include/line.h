//
// Created by ynakanishi on 2020/04/19.
//

#ifndef LINETRACE_SIM_LINE_H
#define LINETRACE_SIM_LINE_H

#include <Eigen/Core>

struct Line{
    Eigen::Vector2d start,end;

    double norm() const{
        return (end - start).norm();
    }
};

#endif //LINETRACE_SIM_LINE_H
