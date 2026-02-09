#include "Timer.h"

Timer::Timer()
{
    lastFrame = steady_clock::now();
    deltaSeconds = 0.0f;
    runTimeLength = steady_clock::duration::zero();
}

void Timer::Tick()
{
    steady_clock::time_point now = steady_clock::now();
    steady_clock::duration frameDuration = now - lastFrame;
    deltaSeconds = duration<float>(frameDuration).count();
    runTimeLength += frameDuration;
    lastFrame = now;
}
