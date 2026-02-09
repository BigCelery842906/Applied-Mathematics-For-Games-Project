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
    
    float GetDeltaTime() const { return deltaSeconds; }
    float GetRunTimeLength() { return duration<float>(runTimeLength).count(); }
    
    void Tick();
};
