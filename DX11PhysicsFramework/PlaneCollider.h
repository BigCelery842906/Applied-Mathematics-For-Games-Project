#pragma once
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

class PlaneCollider : public Collider
{
private:
    Vector3 _colliderSize;
public:
    PlaneCollider(Transform* transform, Vector3 ColliderSize) : Collider(transform, TypePlaneCollider) { _colliderSize = ColliderSize; }

    virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(SphereCollider& other) override;
    virtual bool CollidesWith(BoxCollider& other) override;
    virtual bool CollidesWith(PlaneCollider& other) override;
};
