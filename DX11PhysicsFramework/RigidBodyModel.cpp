#include "RigidBodyModel.h"
#include "DX11PhysicsFramework.h"

RigidBodyModel::RigidBodyModel(Transform* transform, float mass) : PhysicsModel(transform)
{
    _mass = mass;
    XMStoreFloat3x3(&inertiaTensor, XMMatrixIdentity());
    
	Vector3 colliderSize = GetColliderSize();
    inertiaTensor._11 = 1/12 * _mass * (colliderSize.x * colliderSize.x);
    inertiaTensor._12 = 1/12 * _mass * (colliderSize.y * colliderSize.y);
    inertiaTensor._13 = 1/12 * _mass * (colliderSize.z * colliderSize.z);    
}

void RigidBodyModel::Update(float deltaTime)
{
    PhysicsModel::Update(deltaTime);
    calculateAngularVelocity(deltaTime);
}

void RigidBodyModel::AddRelativeForce(Vector3 force, Vector3 posToApply)
{
    PhysicsModel::AddRelativeForce(force, posToApply);
    
    // Cross product is  magnitude of A * magnitude of B * sin (angle between A and B) * n (unit vector at right angle to both A and B)
    // vector / magnitude of vector = unit vector
    
    AddForce(force);
    torque += crossProduct(posToApply, force);
}

void RigidBodyModel::ApplyRelativeImpulse(Vector3 force, Vector3 point)
{
    ApplyImpulse(force);
    torque += force^point;
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
    
    XMVECTOR det;
    XMMATRIX inverseInertiaMatrix = XMMatrixInverse(&det, inertiaTensorMatrix);
    
    float detF = XMVectorGetX(det);
    // float abs
    if (fabsf(detF) < tolerance)
    {
        torque = Vector3();
        return;
    }
    
    XMFLOAT3 torqueV3 = { torque.x, torque.y, torque.z};
    XMVECTOR torqueVector = XMLoadFloat3(&torqueV3);
    
    // angularAcceleration = inverseInertia * torque
    XMVECTOR angularAcceleration = XMVector3Transform(torqueVector, inverseInertiaMatrix);

    XMFLOAT3 angularAccel;
    XMStoreFloat3(&angularAccel, angularAcceleration);

    angularVelocity += Vector3(angularAccel.x, angularAccel.y, angularAccel.z) * deltaTime;
    
    Quaternion orientation = _transform->GetOrientation();

    Quaternion angularQuat(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z);

    // TODO LOOK AT WHY NO WORK
    // q_dot = 0.5 * omega_quat * q
    Quaternion Newquat = angularQuat * orientation;

    // q_new = q + q_dot * dt * 0.5
    orientation += Newquat * (0.5f * deltaTime);

    // Apply angular damping
    angularVelocity *= powf(angularDamping, deltaTime);

    // Normalize quaternion
    float mag = orientation.Magnitude();
    if (mag != 0.0f)
    {
        orientation /= mag;
    }
    else
    {
        // Safeguard: if orientation collapsed, set identity quaternion
        orientation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }

    _transform->SetOrientation(orientation);

    // Clear accumulated torque
    torque = Vector3();
    
    
#pragma region FAILED ATTEMPTS - ...... INDICATES NEW ATTEMPT
    // ........
    // XMFLOAT3 torqueV3 = { torque.x, torque.y, torque.z };
    // XMVECTOR torqueVector = XMLoadFloat3(&torqueV3);
    //
    // XMVECTOR angularAcceleration = XMVector3Transform(torqueVector, inverseInertiaMatrix);
    //
    // XMFLOAT3 angularAccel;
    //
    // XMStoreFloat3(&angularAccel, angularAcceleration);
    //
    // angularVelocity += Vector3(angularAccel.x, angularAccel.y, angularAccel.z) * deltaTime;;
    //
    // Quaternion orientation = _transform->GetOrientation()
    
    // ........
    
    // orientation += orientation * angularVelocity * 0.5 * deltaTime;
    //
    // angularVelocity *= pow(angularDamping,deltaTime);
    //
    // if (orientation.Magnitude() != 0)
    // {
    //     //Normalise
    //     orientation /= orientation.Magnitude();
    // }
    //
    // _transform->SetOrientation(orientation);
    // torque = Vector3();
#pragma endregion
}
