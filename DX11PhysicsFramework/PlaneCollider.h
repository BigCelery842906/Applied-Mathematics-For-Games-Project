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

    virtual bool CollidesWith(Collider& other, Vector3& poc) override { return other.CollidesWith(*this, poc); }
    virtual bool CollidesWith(SphereCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(BoxCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(PlaneCollider& other, Vector3& poc) override;

    virtual void SetColliderSize(Vector3 newColliderSize) override { _colliderSize = newColliderSize; }
};
