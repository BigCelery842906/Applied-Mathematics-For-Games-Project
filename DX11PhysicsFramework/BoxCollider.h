#pragma once
#include <cmath>
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"
#include <algorithm>
#include <iostream>

class BoxCollider : public Collider
{
private:
    Vector3 _colliderSize;
public:
    BoxCollider(Transform* transform, Vector3 colliderSize) : Collider(transform, TypeBoxCollider) { _colliderSize = colliderSize; }
    
    virtual bool CollidesWith(Collider& other, Vector3& poc) override { return other.CollidesWith(*this, poc); }
    virtual bool CollidesWith(SphereCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(BoxCollider& other, Vector3& poc) override;
    virtual bool CollidesWith(PlaneCollider& other, Vector3& poc) override;

    Vector3 GetColliderSize() const { return _colliderSize; }
    
    virtual void SetColliderSize(Vector3 newColliderSize) override { _colliderSize = newColliderSize; }
};
