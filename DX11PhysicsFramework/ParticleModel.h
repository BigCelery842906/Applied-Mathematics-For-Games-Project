#pragma once
#include <vector>

#include "Appearance.h"
#include "GameObject.h"
#include "PhysicsModel.h"
#include "Structures.h"

class DX11PhysicsFramework;
class Particle;

class ParticleModel : public PhysicsModel
{
private:
    float emissionRate = 50.0f;
    float emissionAccumulator = 0.0f;
    float initialParticleSpeed = 5.0f;
    float _resetTime = 0;
    float _aliveTime = 0;
    
    bool _invertGravity = false;
    bool _applyGravity = false;
    bool currentlySpawning = true;
    Vector3 _pertubation = Vector3(0, 0, 0);
    
    int maxNumOfParticles = 500;
    int curParticleCount = 0;

    std::vector<Particle> _particles;
    Appearance* _appearance;

public:
    ParticleModel(Transform* transform, Appearance* particleAppearance, DX11PhysicsFramework* particlePush) : PhysicsModel(transform) {};
    ParticleModel(Transform* transform, Appearance* particleAppearance, DX11PhysicsFramework* particlePush, float resetTime, Vector3 pertubation, bool applyGravity, bool invertGravity = false);

    void Reset();
    void Update(float deltaTime) override;
    void EmitParticle();

    static Vector3 RandomVectorInRange(const Vector3& range);
    
    virtual void AddRelativeForce(Vector3 force, Vector3 posToApply) override { AddForce(force); }
    
    
    void SpawnParticles(DX11PhysicsFramework* particlePush);
    void DecrementParticleCount() {curParticleCount--;};
    
    void ToggleParticleSpawn() {currentlySpawning = !currentlySpawning;};
};


class Particle : public GameObject
{
private:
    ParticleModel* _particleParent = nullptr;
    Vector3 _spawnLocation;
    float _maxLifeTime = 5.0f;
    float _lifeTime = 0.0f;
    bool isCurrentlyRendering = false;

public:
    // GameObject(string type, Appearance* _appearance, float mass = 1.0f);
    Particle(ParticleModel* parentModel, Appearance* appearance, float maxLifeTime = 5.0f) : GameObject("Particle", appearance) {_particleParent = parentModel; isCurrentlyRendering = false;};
    void Update(float deltaTime);
    void ResetParticle();
    
    void SetMaxLifeTime(float maxLifeTime) {_maxLifeTime = maxLifeTime;}
    float GetMaxLifeTime() {return _maxLifeTime;}
    
    void SetLifeTime(float time) {_lifeTime = time;}
    float GetLifeTime() {return _lifeTime;}
    
    void SetSpawnLocation(Vector3 spawnLocation) {_spawnLocation = spawnLocation;};
    
    void SetRenderingBool(bool rendering) {isCurrentlyRendering = rendering;};
    bool GetRenderingBool() {return isCurrentlyRendering;};
    
};