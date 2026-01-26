#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
private:
    float _resetTime;
    float _aliveTime;
    
    bool _invertGravity;
    Vector3 _pertubation;
public:
    ParticleModel(Transform* transform) : PhysicsModel(transform) {};
    ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool invertGravity);

    void Reset();
    void Update(float deltaTime) override;
    
    
};
