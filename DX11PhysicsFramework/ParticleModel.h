#pragma once
#include "PhysicsModel.h"

class ParticleModel : public PhysicsModel
{
private:
    float _resetTime = 0;
    float _aliveTime = 0;
    
    bool _invertGravity = false;
    Vector3 _pertubation = Vector3(0, 0, 0);
    
    int maxNumOfParticles = 100;
    int curParticle = 0;
    
public:
    ParticleModel(Transform* transform) : PhysicsModel(transform) {};
    ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool invertGravity);

    void Reset();
    void Update(float deltaTime) override;
    void SpawnParticle();
    
    virtual void AddRelativeForce(Vector3 force, Vector3 posToApply) override { AddForce(force); }
};
