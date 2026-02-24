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
    
    virtual bool CollidesWith(Collider& other, Vector3& poc) override { return other.CollidesWith(*this, poc); }
    virtual bool CollidesWith(SphereCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(BoxCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(PlaneCollider& other, Vector3& poc) override;
    
    float GetRadius() const { return _radius; }

    virtual void SetColliderSize(Vector3 newColliderSize) override { _radius = newColliderSize.x; }
};