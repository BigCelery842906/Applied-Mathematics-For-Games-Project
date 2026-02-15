#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

bool BoxCollider::CollidesWith(SphereCollider& other)
{
    float otherRadius = other.GetRadius();
    Vector3 colliderSize = GetColliderSize();
    Vector3 combinedCollideSize = Vector3((colliderSize.x + otherRadius), (colliderSize.y + otherRadius), (colliderSize.z + otherRadius));
    
    Vector3 transformDifference = GetPosition() - other.GetPosition();
    
    if (transformDifference.x > combinedCollideSize.x)
    {
        DebugPrintF("Collision from Box Object on X \n");
        return true;
    }
    if (transformDifference.y > combinedCollideSize.y)
    {
        DebugPrintF("Collision from Box Object on Y \n");
        return true;
    }
    if (transformDifference.z > combinedCollideSize.z)
    {
        DebugPrintF("Collision from Box Object on Z \n");
        return true;
    }
    
    return false;
}
bool BoxCollider::CollidesWith(BoxCollider& other)
{
    Vector3 combinedBoxSize = GetColliderSize() + other.GetColliderSize();
    
    Vector3 transformDifference = GetPosition() - other.GetPosition();
    float transformMagnitude = transformDifference.Magnitude();
    
    if (combinedBoxSize.Magnitude() > transformMagnitude)
    {
        DebugPrintF("BoxCollider::CollidesWith(BoxCollider& other)\n");
        return true;
    }
    
    return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other)
{
    return other.CollidesWith(*this);
}
