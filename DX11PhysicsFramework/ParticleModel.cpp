#include "ParticleModel.h"
#include "GameObject.h"

#include <algorithm>

#include "DX11PhysicsFramework.h"

ParticleModel::ParticleModel(Transform* transform, Appearance* particleAppearance, DX11PhysicsFramework* particlePush, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity) : PhysicsModel(transform)
{
    _resetTime = resetTime;
    _pertubation = pertubation;
    _applyGravity = applyGravity;
    _invertGravity = invertGravity;
    _appearance = particleAppearance;

    // Spawn all particles now to avoid expensive instantiations during the rest of runtime
	_particles.reserve(maxNumOfParticles); // Reserve space for all potential particles
    SpawnParticles(particlePush);
}

void ParticleModel::Reset()
{
    // Reset Logic here
	_particles.clear();
	curParticleCount = 0;
	emissionAccumulator = 0.0f;
}

void ParticleModel::Update(float deltaTime)
{
    PhysicsModel::Update(deltaTime);
    
    if (currentlySpawning)
    {
        emissionAccumulator += deltaTime * emissionRate;
    
        while (emissionAccumulator >= 1.0f)
        {
            EmitParticle();
            emissionAccumulator -= 1.0f;
        }
    }    
}

void ParticleModel::EmitParticle()
{
    if (curParticleCount < maxNumOfParticles)
    {
        for (auto& particle: _particles)
        {
            if (!particle.GetRenderingBool())
            {
                // In case the emitter has moved locations
                Vector3 spawnLocation = _transform->GetPosition();
                particle.GetTransform()->SetPosition(spawnLocation);
                particle.SetSpawnLocation(spawnLocation);
    
                Vector3 randomDirection = RandomVectorInRange(_pertubation);
                randomDirection.Normalize();
                particle.GetPhysicsModel()->SetForceApply(true);
                particle.GetPhysicsModel()->SetVelocity(randomDirection * initialParticleSpeed);
        
                particle.SetRenderingBool(true);
                curParticleCount++;
                break;
            }
        }
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

void ParticleModel::SpawnParticles(DX11PhysicsFramework* particlePush)
{
    for (int i = 0; i < maxNumOfParticles; i++)
    {
        Particle particle(this, _appearance, _resetTime);
        Vector3 spawnLocation = _transform->GetPosition();
        particle.GetTransform()->SetPosition(spawnLocation);
        particle.SetSpawnLocation(spawnLocation);
        particle.GetTransform()->SetScale(_transform->GetScale() * 0.5);
        
        particle.GetPhysicsModel()->SetForceApply(false);
        particle.GetPhysicsModel()->SetVelocity(Vector3());
        
        particle.SetRenderingBool(false);
        if (_applyGravity)
        {
            if (_invertGravity)
            {
                particle.GetPhysicsModel()->SetAcceleration(-GravityForce());
            }
            else
            {
                particle.GetPhysicsModel()->SetAcceleration(GravityForce());
            }
        }
        else
        {
            particle.GetPhysicsModel()->SetAcceleration(Vector3());
        }

        _particles.push_back(std::move(particle));
    }

    // Push the particles back into the dx11 framework so they can be added to the draw call 
    particlePush->PushParticles(_particles);
}

void Particle::Update(float deltaTime)
{
    if (isCurrentlyRendering) // Only call if the particle is in use
    {
        GameObject::Update(deltaTime);
        _lifeTime += deltaTime;
        if (_lifeTime > _maxLifeTime)
        {
            ResetParticle();
            _particleParent->DecrementParticleCount();
        }
    }
}

void Particle::ResetParticle()
{
    // Reset this particle back to the emitter and stop drawing it
    isCurrentlyRendering = false;
    GetTransform()->SetPosition(_spawnLocation);
    _lifeTime = 0.0f;
    GetPhysicsModel()->SetForceApply(false);
    GetPhysicsModel()->SetVelocity(Vector3());
    GetPhysicsModel()->SetAcceleration(Vector3());
    
}
