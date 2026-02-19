#include "ParticleModel.h"

#include <algorithm>
#include <ctime>

#include "GameObject.h"

ParticleModel::ParticleModel(Transform* transform, Appearance* particleAppearance, DX11PhysicsFramework* particlePush, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity) : PhysicsModel(transform)
{
    _resetTime = resetTime;
    _pertubation = pertubation;
    _applyGravity = applyGravity;
    _invertGravity = invertGravity;
    _appearance = particleAppearance;

	_particles.reserve(maxNumOfParticles); // Reserve space for all potential particles
    
    SpawnParticles(particlePush);
}

void ParticleModel::Reset()
{
    // Reset Logic here
	_particles.clear();
	curParticleCount = 0;
	emissionAccumulator = 0.0f;
	_aliveTime = 0.0f;
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
        // particle.lifeTime -= deltaTime;
        
        // if (particle.lifeTime <= 0.0f)
        {
            //Kill particle
			// std::remove_if combined with erase to remove dead particles
			// beginning of vector, end of vector, function that returns true if particle is dead
            // https://www.geeksforgeeks.org/cpp/std-remove-if-algorithm-in-cpp-stl/
            //_particles.erase
        }
    }
}

void ParticleModel::EmitParticle()
{
   
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
        GameObject particle("Particle", _appearance);
        particle.GetTransform()->SetPosition(_transform->GetPosition());
        
        Vector3 randomDirection = RandomVectorInRange(_pertubation);
        randomDirection.Normalize();
        particle.GetPhysicsModel()->SetForceApply(false);
        particle.GetPhysicsModel()->SetVelocity(randomDirection * initialParticleSpeed);
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
        //
        // particle.lifeTime = _resetTime;
        // particle.maxLifeTime = _resetTime;

        // Move the locally-created particle into the vector
        _particles.push_back(std::move(particle));
    }

    particlePush->PushParticles(_particles);
}
