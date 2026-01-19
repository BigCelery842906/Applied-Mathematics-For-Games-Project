#include "Timer.h"
using namespace std::chrono;

Timer::Timer()
{
    lastFrame = steady_clock::now();
}

float Timer::GetDeltaTime()
{
    return duration<float>(steady_clock::now() - lastFrame).count();
    
}

float Timer::GetRunTimeLength()
{
    return duration<float>(runTimeLength).count();
}

void Timer::Tick()
{
    lastFrame = steady_clock::now();
    
    //Debug somewhere along here for runtime
}
