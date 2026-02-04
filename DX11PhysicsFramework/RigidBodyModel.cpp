#include "RigidBodyModel.h"

RigidBodyModel::RigidBodyModel(Transform* transform, float mass) : PhysicsModel(transform)
{
    _mass = mass;
}

void RigidBodyModel::Update(float deltaTime)
{
    PhysicsModel::Update(deltaTime);
}
