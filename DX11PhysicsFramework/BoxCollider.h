#pragma once
#include <cmath>
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

class BoxCollider : public Collider
{
private:
    Vector3 _colliderSize;
public:
    BoxCollider(Transform* transform, Vector3 colliderSize) : Collider(transform, TypeBoxCollider) { _colliderSize = colliderSize; }
    
    virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(SphereCollider& other) override;
    virtual bool CollidesWith(BoxCollider& other) override;
    virtual bool CollidesWith(PlaneCollider& other) override;

    Vector3 GetColliderSize() const { return _colliderSize; }
    
    virtual void SetColliderSize(Vector3 newColliderSize) override { _colliderSize = newColliderSize; }
};
