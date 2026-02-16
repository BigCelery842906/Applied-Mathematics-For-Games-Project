#pragma once
#include <vector>

#include "PhysicsModel.h"
#include "Structures.h"

class ParticleModel : public PhysicsModel
{
private:
    float emissionRate = 5.0f;
    float emissionAccumulator = 0.0f;
    float initialParticleSpeed = 1.0f;
    float _resetTime = 0;
    float _aliveTime = 0;
    
    bool _invertGravity = false;
    bool _applyGravity = false;
    Vector3 _pertubation = Vector3(0, 0, 0);
    
    int maxNumOfParticles = 100;
    int curParticleCount = 0;

    std::vector<Particle> _particles;

public:
    ParticleModel(Transform* transform) : PhysicsModel(transform) {};
    ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity = false);

    void Reset();
    void Update(float deltaTime) override;
    void EmitParticle();

    static Vector3 RandomVectorInRange(const Vector3& range);
    
    virtual void AddRelativeForce(Vector3 force, Vector3 posToApply) override { AddForce(force); }
};
