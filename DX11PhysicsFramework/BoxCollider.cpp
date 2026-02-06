#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

bool BoxCollider::CollidesWith(SphereCollider& other)
{
    return false;
}
bool BoxCollider::CollidesWith(BoxCollider& other)
{
    return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other)
{
    return other.CollidesWith(*this);
}
