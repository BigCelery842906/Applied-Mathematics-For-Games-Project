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
    
    virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(SphereCollider& other) override;
    virtual bool CollidesWith(BoxCollider& other) override;
    virtual bool CollidesWith(PlaneCollider& other) override;
    
    float GetRadius() const { return _radius; }
};
