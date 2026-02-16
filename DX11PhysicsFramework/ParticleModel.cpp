#include "ParticleModel.h"

#include <algorithm>
#include <ctime>

ParticleModel::ParticleModel(Transform* transform, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity) : PhysicsModel(transform)
{
    _resetTime = resetTime;
    _pertubation = pertubation;
    _applyGravity = applyGravity;
    _invertGravity = invertGravity;

	_particles.reserve(maxNumOfParticles); // Reserve space for all potential particles
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
        particle.velocity += particle.acceleration * deltaTime;
        particle.position += particle.velocity * deltaTime;
        particle.lifeTime -= deltaTime;
        
        if (particle.lifeTime <= 0.0f)
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