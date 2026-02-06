#pragma once
#include "Appearance.h"
#include "Collider.h"

class PlaneCollider : public Collider
{
private:
    Vector3 _colliderSize;
public:
    PlaneCollider(Transform* transform, Vector3 ColliderSize) : Collider(transform) { _colliderSize = ColliderSize; }

    virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(SphereCollider& other) override;
    virtual bool CollidesWith(BoxCollider& other) override;
    virtual bool CollidesWith(PlaneCollider& other) override;
    
};
