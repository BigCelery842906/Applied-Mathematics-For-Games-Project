#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool invertGravity) : PhysicsModel(transform)
{
    _resetTime = resetTime;
    _pertubation = pertubation;
    _invertGravity = invertGravity;
}

void ParticleModel::Reset()
{
    // Reset Logic here
}

void ParticleModel::Update(float deltaTime)
{
    _aliveTime += deltaTime;
    if (_aliveTime > _resetTime)
    {
        Reset();
    }
    
    if (_simulateGravity)
    {
        _netForce += GravityForce();
    }
    
    PhysicsModel::Update(deltaTime);
}

void ParticleModel::SpawnParticle()
{
    if (curParticle < maxNumOfParticles)
    {
        
    }
}
