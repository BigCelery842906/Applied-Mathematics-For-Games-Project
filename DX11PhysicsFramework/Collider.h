#pragma once

#include "Transform.h"

class SphereCollider;
class BoxCollider;
class PlaneCollider;

enum ColliderType
{
    TypeCollider,
    TypeSphereCollider,
    TypeBoxCollider,
    TypePlaneCollider
};

class Collider abstract
{
    protected:
    Transform* _transform;
    ColliderType _type;
public:
    Collider(Transform* transform, ColliderType type = TypeCollider) {_transform = transform; _type = type; }
    
    virtual bool CollidesWith(Collider& other) = 0;
    virtual bool CollidesWith(SphereCollider& other) = 0;
    virtual bool CollidesWith(BoxCollider& other) = 0;
    virtual bool CollidesWith(PlaneCollider& other) = 0;
    
    Vector3 GetPosition() const {return _transform->GetPosition();}
    
    ColliderType GetColliderType() const {return _type;}
    
};
