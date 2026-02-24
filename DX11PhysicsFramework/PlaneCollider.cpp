#include "PlaneCollider.h"

// THIS IS NOT IMPLEMENTED AS A WHOLE - NO PLANE COLLIDER USED ANYWHERE
bool PlaneCollider::CollidesWith(SphereCollider& other, Vector3& poc)
{
    return false;
}

bool PlaneCollider::CollidesWith(BoxCollider& other, Vector3& poc)
{
    return false;
}

bool PlaneCollider::CollidesWith(PlaneCollider& other, Vector3& poc)
{ //This will rarely ever need to be checked to my knowledge
    return false;
}