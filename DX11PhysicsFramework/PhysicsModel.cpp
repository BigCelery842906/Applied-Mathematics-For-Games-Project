#include "PhysicsModel.h"

#include "Appearance.h"

PhysicsModel::PhysicsModel(Transform* transform, float mass)
{
    _transform = transform;
    _mass = mass;
    _netForce = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsModel::Update(float deltaTime)
{
    Vector3 position = _transform->GetPosition();
    // if (isConstantVelocity)
    // {
    //     _velocity = _constantVelocity;
    // }
    //
    // if (isConstantAccelerate)
    // {
    //     _velocity += _constantAcceleration * deltaTime;
    // }
    
    if (position.y > 1) //Until collision works, use this wrap for gravity/friction
    {
        if (_simulateGravity)
        {
            _netForce += GravityForce();
        }
    }
    else
    {
        if (_simulateGravity)
        {
            _velocity.y = 0; //Just until I can get actual collision going
        }
        _netForce += FrictionForce();
    }
    _netForce += DragForce();
    _acceleration = _netForce / _mass;
    _velocity += _acceleration * deltaTime;
    
    position += _velocity * deltaTime;
    _transform->SetPosition(position);
    
    _netForce = Vector3(0.0f, 0.0f, 0.0f);
    _acceleration = Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 PhysicsModel::GravityForce()
{
    return Vector3(0, -9.81f, 0) * _mass;
}

Vector3 PhysicsModel::DragForce()
{
    // Equation on sheet is this:
    // F(n) = 1/2 * p * v^2 * C(n) * A;
    //Which returns a float
    // return  0.5 * _density * (_velocity * _velocity) * _dragCoefficient * _crossSectionalArea;
    
    //Create a copy of velocity
    Vector3 velocity = _velocity;
    
    //Negating
    velocity *= -1;
    //Normalising
    velocity.Normalize();
    //Multiply by scalar
    velocity *= _dragCoefficient;
    
    // float velocityMagnitude = velocity.Magnitude(); //Used if want to make it a float, then return velocityMagnitude
    
    //return value
    return velocity;
}

Vector3 PhysicsModel::FrictionForce()
{
    // F(f) = u(k) * F(n);
    float u = 1.05; // Frictional Coefficient according to sam - Changes depending on surfaces involved
    return u * DragForce();
}
