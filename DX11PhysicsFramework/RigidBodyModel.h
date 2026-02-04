#pragma once
#include "PhysicsModel.h"

class RigidBodyModel : public PhysicsModel
{
public:
    RigidBodyModel(Transform* transform, float mass = 1.0f);
    void Update(float deltaTime) override;
};
