#include "PlaneCollider.h"

bool PlaneCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    return false;
}

bool PlaneCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
    return false;
}

bool PlaneCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{ //This will rarely ever need to be checked to my knowledge
    return false;
}
