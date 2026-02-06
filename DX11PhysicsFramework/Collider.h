#pragma once

#include "Transform.h"

class SphereCollider;
class BoxCollider;
class PlaneCollider;

class Collider abstract
{
    protected:
    Transform* _transform;
public:
    Collider(Transform* transform) {_transform = transform;}
    
    virtual bool CollidesWith(Collider& other) = 0;
    virtual bool CollidesWith(SphereCollider& other) = 0;
    virtual bool CollidesWith(BoxCollider& other) = 0;
    virtual bool CollidesWith(PlaneCollider& other) = 0;
    
    Vector3 GetPosition() const {return _transform->GetPosition();}
    
};
