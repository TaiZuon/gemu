#pragma once

#include "../Constant.hpp"
class Timer
{
private:
    static Timer* g_Instance;
    double gDelta_Time;
    double gLast_Time;
    
public:
    Timer(){}
    static Timer* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Timer();
    }
    void Tick();
    double Get_Delta_Time()
    {
        return gDelta_Time;
    }

};


