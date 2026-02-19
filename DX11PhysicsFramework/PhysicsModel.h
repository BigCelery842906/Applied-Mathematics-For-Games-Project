#pragma once
#include "Collider.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"
#include "SphereCollider.h"

class PhysicsModel abstract
{
protected:
    Transform *_transform;
    Vector3 _velocity;
    Vector3 _acceleration;
    
    Vector3 _constantVelocity;
    Vector3 _constantAcceleration;
    
    Vector3 _netForce;
    float _mass = 1.0f;
    
    bool _simulateGravity = false;
    bool _colliding = false;
    
    float _density = 1.0f;
    float _dragCoefficient = 0.9f;
    float _crossSectionalArea = 1.0f;
    
    Collider* _collider = nullptr;
    
    float tolerance = 0.001f;
    
    bool _applyForces = true;
    
public:
    PhysicsModel(Transform* transform, float mass = 1.0f);
    virtual void Update(float deltaTime);

    virtual void simulateGravity(bool value) { _simulateGravity = value; }
    virtual void AddForce(Vector3 force) { _netForce += force; }
    
    Vector3 GravityForce();
    Vector3 DragForce();
    Vector3 FrictionForce();
    
    bool IsCollideable() const { return _collider != nullptr; }
    void isCurrentlyColliding(bool value) { _colliding = value; }
    Collider* GetCollider() const { return _collider; }
    
    void SetCollider(Collider* collider) { _collider = collider; }
    Vector3 GetColliderSize();
    
    
    Vector3 GetVelocity() const { return _velocity; }
    void SetVelocity(Vector3 velocity) { _velocity = velocity; }
    
    Vector3 GetAcceleration() const { return _acceleration; }
    void SetAcceleration(Vector3 acceleration) { _acceleration = acceleration; }
    
    float GetMass() const { return _mass; }
    float GetInverseMass() const;
    
    void ApplyImpulse(Vector3 impulse);
    virtual void AddRelativeForce(Vector3 force, Vector3 posToApply) {};
    virtual void ApplyRelativeImpulse(Vector3 force, Vector3 point) {};
    
    void SetForceApply(bool value) { _applyForces = value; }
};
