#pragma once
#include "PhysicsModel.h"
#include "Quaternion.h"

class RigidBodyModel : public PhysicsModel
{
    XMFLOAT3X3 inertiaTensor;
    float angularDamping = 0.99f; // 1 means never stop, 0 means instantly
    
    Vector3 angularVelocity = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 torque;
public:
    RigidBodyModel(Transform* transform, float mass = 1.0f);
    void Update(float deltaTime) override;
    
    virtual void AddRelativeForce(Vector3 force, Vector3 posToApply) override;
    virtual void ApplyRelativeImpulse(Vector3 force, Vector3 point) override;
    Vector3 crossProduct(Vector3 a, Vector3 b);
    
    Vector3 GetAngularVelocity() const { return angularVelocity; }
    void calculateAngularVelocity(float deltaTime);
};
