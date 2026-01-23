#include "PhysicsModel.h"

PhysicsModel::PhysicsModel(Transform* transform)
{
    _transform = transform;
}

void PhysicsModel::Update(float deltaTime)
{
    Vector3 position = _transform->GetPosition();
    _velocity += _acceleration * deltaTime;
    position += _velocity * deltaTime;
    _transform->SetPosition(position);
}
