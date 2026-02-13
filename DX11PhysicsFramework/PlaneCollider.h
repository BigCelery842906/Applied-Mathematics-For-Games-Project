#pragma once
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Structures.h"

class PlaneCollider : public Collider
{
private:
    Vector3 _colliderSize;
public:
    PlaneCollider(Transform* transform, Vector3 ColliderSize) : Collider(transform, TypePlaneCollider) { _colliderSize = ColliderSize; }

    virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
    virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
    virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
    virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;

    virtual void SetColliderSize(Vector3 newColliderSize) override { _colliderSize = newColliderSize; }
};
