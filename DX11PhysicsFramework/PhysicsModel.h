#pragma once
#include "Transform.h"


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
    
    float _density = 1.0f;
    float _dragCoefficient = 0.9f;
    float _crossSectionalArea = 1.0f;
    
public:
    PhysicsModel(Transform* transform, float mass = 1.0f);
    virtual void Update(float deltaTime);
    
    // Vector3 GetVelocity() { return _velocity; }
    // void SetVelocity(Vector3 velocity) { _velocity = velocity; }
    
    // bool IsConstantlyAccelerating() { return isConstantAccelerate; }
    // void ToggleConstantAcceleration() { isConstantAccelerate = !isConstantAccelerate; }
    
    void simulateGravity(bool value) { _simulateGravity = value; }
    void AddForce(Vector3 force) { _netForce += force; }
    
    Vector3 GravityForce();
    
    Vector3 DragForce();
    Vector3 FrictionForce();
};
