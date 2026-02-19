#include "PhysicsModel.h"

PhysicsModel::PhysicsModel(Transform* transform, float mass)
{
    _transform = transform;
    _mass = mass;
    _netForce = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsModel::Update(float deltaTime)
{
    if (_mass == 0)
    { // Catch on 0 Mass to prevent any NaN errors
        return;
    }
    Vector3 position = _transform->GetPosition();
    if (_applyForces)
    {
        if (_simulateGravity)
        {
            _netForce += GravityForce();
        }
        if (_colliding)
        {
            _netForce += FrictionForce();
        }
    
        _netForce += DragForce();
        _acceleration = _netForce / _mass;
    }
    _velocity += _acceleration * deltaTime;
    
    if (_velocity.Magnitude() < tolerance)
    {
        _velocity = Vector3(0, 0, 0);
    }
    position += _velocity * deltaTime;
    _transform->SetPosition(position);
    
    //Reset forces and acceleration each frame
    _netForce = Vector3(0.0f, 0.0f, 0.0f);
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 PhysicsModel::GravityForce()
{
    return Vector3(0, -9.81f, 0) * _mass;
}

Vector3 PhysicsModel::DragForce()
{
    // TODO CHECK WHETHER THIS IS CORRECT
    // Equation on sheet is this:
    // F(n) = 1/2 * p * v^2 * C(n) * A;
    //Which returns a float
    // return  0.5 * _density * (_velocity * _velocity) * _dragCoefficient * _crossSectionalArea;
    
    //Create a copy of velocity
    Vector3 velocity = _velocity;
    
    // //Negating
    // velocity *= -1;
    // //Normalising to get direction
    // velocity.Normalize();
    // // velocity.x *= velocity.x;
    // // velocity.y *= velocity.y;
    // // velocity.z *= velocity.z;
    //
    // //Multiply by scalar
    // velocity *= _dragCoefficient * _crossSectionalArea * _density * 0.5;
    
    float floatValues = _density * _dragCoefficient * _crossSectionalArea * -1;
    velocity = Vector3 (velocity.x * floatValues, velocity.y * floatValues, velocity.z * floatValues);
    
    //return value
    return velocity;
}

Vector3 PhysicsModel::FrictionForce()
{
    // F(f) = u(k) * F(n);
    float u = 1.5; // Frictional Coefficient according to sam - Changes depending on surfaces involved
    return u * DragForce();
}

Vector3 PhysicsModel::GetColliderSize()
{
    if (_collider)
    {
        switch (_collider->GetColliderType())
        {
        case TypeCollider:
            {
                Collider* collider = dynamic_cast<Collider*>(_collider);
                break;
            }
        case TypeBoxCollider:
            {
                BoxCollider* collider = dynamic_cast<BoxCollider*>(_collider);
                return collider->GetColliderSize();
                break;
            }
        case TypePlaneCollider:
            { // TODO NOT YET IMPLEMENTED
                PlaneCollider* collider = dynamic_cast<PlaneCollider*>(_collider);
                break;
            }
        case TypeSphereCollider:
            {
                SphereCollider* collider = dynamic_cast<SphereCollider*>(_collider);
                float radius = collider->GetRadius();
                return Vector3 (radius, radius, radius);
                break;
            }
        }
    }
    
    return Vector3(0, 0, 0);
}

void PhysicsModel::ApplyImpulse(Vector3 impulse)
{
    _velocity += impulse;
}

float PhysicsModel::GetInverseMass() const
{
    if (_mass == 0)
    {
        return 0;
    }
    return 1.0f / _mass;
}
