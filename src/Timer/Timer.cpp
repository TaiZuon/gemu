#include "Timer.hpp"
#include "SDL.h"
#include <iostream>


Timer* Timer::g_Instance = nullptr;

void Timer::Tick()
{
    gDelta_Time = (SDL_GetTicks() - gLast_Time) * (FPS/1000.0);
    gDelta_Time = std::min(gDelta_Time, DELTA_TIME);

    gLast_Time = SDL_GetTicks();
}