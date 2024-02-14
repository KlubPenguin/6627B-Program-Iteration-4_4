#pragma once

#include "api.h"
#include "ios.hpp"


class Pos
{
    private:
    double x;
    double y;
    double theta;

    public:
    Pos(double X, double Y, double THETA)
    {
        x = X;
        y = Y;
        theta = THETA;
    }

    void move(double increment)
    {
        x += increment * sin(toRad(theta));
        y += increment * cos(toRad(theta));
    }

    void align()
    {
        x = chassis.getPose().x;
        y = chassis.getPose().y;
        theta = chassis.getPose().theta;
    }

    double newX()
    {
        return x;
    }

    double newY()
    {
        return y;
    }

    double newTheta()
    {
        return theta;
    }

    void turn(double angle)
    {
        x += sin(toRad(angle));
        y += cos(toRad(angle));
        
    }
};

