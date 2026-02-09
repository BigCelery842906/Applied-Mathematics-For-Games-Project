#include "RigidBodyModel.h"
#include "DX11PhysicsFramework.h"

RigidBodyModel::RigidBodyModel(Transform* transform, float mass) : PhysicsModel(transform)
{
    _mass = mass;
    inertiaTensor =  XMFLOAT3X3(
        1, 0, 0, 
        0, 1, 0, 
        0, 0, 1);
}

void RigidBodyModel::Update(float deltaTime)
{
    PhysicsModel::Update(deltaTime);
    calculateAngularVelocity(deltaTime);
}

void RigidBodyModel::AddRelativeForce(Vector3 force, Vector3 posToApply)
{
    ColliderType type = GetCollider()->GetColliderType();
    if (type)
    {
        if (type == TypeBoxCollider)
        {
            Vector3 colliderSize = GetColliderSize();
            inertiaTensor._11 = (1/12 * _mass * ((colliderSize.y * colliderSize.y) + (colliderSize.z * colliderSize.z)));
            inertiaTensor._12 = (1/12 * _mass * ((colliderSize.x * colliderSize.x) + (colliderSize.z * colliderSize.z)));
            inertiaTensor._13 = (1/12 * _mass * ((colliderSize.z * colliderSize.z) + (colliderSize.y * colliderSize.y)));
        }
        else if (type == TypeSphereCollider)
        {
            float valueToSet = (2/5) * _mass * GetColliderSize().x;
            inertiaTensor._11 = valueToSet;
            inertiaTensor._12 = valueToSet;
            inertiaTensor._13 = valueToSet;
        }
    }
    torque = crossProduct(posToApply, force);    
}

Vector3 RigidBodyModel::crossProduct(Vector3 a, Vector3 b)
{
    Vector3 result = Vector3(0, 0, 0);
    
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

void RigidBodyModel::calculateAngularVelocity(float deltaTime)
{
    if (_mass == 0)
    {
        return;
    }
    
    XMMATRIX inertiaTensorMatrix = XMLoadFloat3x3(&inertiaTensor);
    XMMATRIX inverseInertiaMatrix = XMMatrixInverse(nullptr, inertiaTensorMatrix);
    
    XMFLOAT3 torqueV3 = { torque.x, torque.y, torque.z };
    XMVECTOR torqueVector = XMLoadFloat3(&torqueV3);
    
    XMVECTOR angularAcceleration = XMVector3Transform(torqueVector, inverseInertiaMatrix);
    XMFLOAT3 angularAccel;
    XMStoreFloat3(&angularAccel, angularAcceleration);
    angularVelocity += Vector3((angularAccel.x * deltaTime), (angularAccel.y * deltaTime), (angularAccel.z * deltaTime));
    
    Quaternion orientation = _transform->GetOrientation();
    
    Quaternion omegaQ(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z);

    // TODO LOOK AT WHY NO WORK
    // q_dot = 0.5 * omega_quat * q
    Quaternion qDot = omegaQ * orientation;

    // integrate: q_new = q + q_dot * dt * 0.5  (qDot already contains the 0.5 factor above if you choose)
    // (we used qDot = omega * q, so multiply by 0.5 here)
    orientation += qDot * (0.5f * deltaTime);
    
    // orientation += orientation * angularVelocity * 0.5 * deltaTime;
    
    if (orientation.Magnitude() != 0)
    {
        //Normalise
        orientation /= orientation.Magnitude();
    }
    else
    {
        orientation = Quaternion();
    }
    
    _transform->SetOrientation(orientation);
    
    angularVelocity *= pow(angularDamping,deltaTime);
}
