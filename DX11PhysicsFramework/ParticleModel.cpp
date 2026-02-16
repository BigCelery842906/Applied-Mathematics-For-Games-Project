#include "ParticleModel.h"

#include <algorithm>
#include <ctime>

ParticleModel::ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity) : PhysicsModel(transform)
{
    _resetTime = resetTime;
    _pertubation = pertubation;
    _applyGravity = applyGravity;
    _invertGravity = invertGravity;
}

void ParticleModel::Reset()
{
    // Reset Logic here
}

void ParticleModel::Update(float deltaTime)
{
    emissionAccumulator += deltaTime * emissionRate;
    
    while (emissionAccumulator >= 1.0f)
    {
        EmitParticle();
        emissionAccumulator -= 1.0f;
    }
    
    // PARTICLE UPDATE
    
    for (auto& particle : _particles)
    {
        particle.velocity += particle.acceleration * deltaTime;
        particle.position += particle.velocity * deltaTime;
        particle.lifeTime -= deltaTime;
        
        if (particle.lifeTime <= 0.0f)
        {
            //Kill particle
        }
    }
}

void ParticleModel::EmitParticle()
{
    if (curParticleCount < maxNumOfParticles)
    {
        Particle particle;
        particle.position = _transform->GetPosition();
        
        Vector3 randomDirection = RandomVectorInRange(_pertubation);
        randomDirection.Normalize();
        particle.velocity = randomDirection * initialParticleSpeed;
        if (_applyGravity)
        {
            if (_invertGravity)
            {
                particle.acceleration = -GravityForce();
            }
            else
            {
                particle.acceleration = GravityForce();
            }
        }
        else
        {
            particle.acceleration = Vector3();
        }
        
        particle.lifeTime = _resetTime;
        particle.maxLifeTime = _resetTime;
        
        _particles.push_back(particle);
        
        curParticleCount++;
    }
}

Vector3 ParticleModel::RandomVectorInRange(const Vector3& range)
{
    return Vector3(
        ((float)rand() / RAND_MAX - 0.5f) * range.x,
        ((float)rand() / RAND_MAX - 0.5f) * range.y,
        ((float)rand() / RAND_MAX - 0.5f) * range.z
    );
}