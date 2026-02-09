#include "PlaneCollider.h"

bool PlaneCollider::CollidesWith(SphereCollider& other)
{
    return false;
}

bool PlaneCollider::CollidesWith(BoxCollider& other)
{
    return false;
}

bool PlaneCollider::CollidesWith(PlaneCollider& other)
{ //This will rarely ever need to be checked to my knowledge
    return false;
}
