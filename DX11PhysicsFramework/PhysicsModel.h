#pragma once
#include "Transform.h"


class PhysicsModel
{
protected:
    Transform *_transform;
    Vector3 _velocity;
    Vector3 _acceleration;
    
    bool isAccelerating = false;
    
public:
    PhysicsModel(Transform* transform);
    void Update(float deltaTime);
    
    Vector3 GetVelocity() { return _velocity; }
    void SetVelocity(Vector3 velocity) { _velocity = velocity; }
    
    Vector3 GetAcceleration() { return _acceleration; }
    void SetAcceleration(Vector3 acceleration) { _acceleration = acceleration; }
    
    bool IsAccelerating() { return isAccelerating; }
    void ToggleAccelerating() { isAccelerating = !isAccelerating; }
};
