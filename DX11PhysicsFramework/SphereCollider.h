#pragma once
#include "Collider.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

class SphereCollider : public Collider
{
private:
    float _radius = 1.0f;
public:
    SphereCollider(Transform* transform, float radius) : Collider(transform, TypeSphereCollider) { _radius = radius; }
    
    virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
    virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
    virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
    virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;
    
    float GetRadius() const { return _radius; }

    virtual void SetColliderSize(Vector3 newColliderSize) override { _radius = newColliderSize.x; }
};
