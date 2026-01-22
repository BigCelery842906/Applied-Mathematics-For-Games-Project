#pragma once
#include <chrono>

using namespace std::chrono;

//Could add average frame delta later

class Timer
{
private:
    steady_clock::time_point lastFrame;
    steady_clock::duration runTimeLength;
    float deltaSeconds;
public:
    Timer();
    
    float GetDeltaTime();
    float GetRunTimeLength();
    void Tick();
    
};
