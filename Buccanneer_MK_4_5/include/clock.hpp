#pragma once


class Clock{
    private:
    int interval = 0;

    int time = 0;

    public:
    Clock(int delay)
    {
        interval = delay;
    } 

    int getTime()
    {
        return time;
    }

    void delay()
    {
        time += interval;
    }

    void reset()
    {
        time = 0;
    }
};