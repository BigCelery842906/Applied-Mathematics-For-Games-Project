#include "SphereCollider.h"

#include "Debug.h"

bool SphereCollider::CollidesWith(SphereCollider& other)
{
    float combinedRadius = GetRadius() + other.GetRadius();
    Vector3 transformDifference = GetPosition() - other.GetPosition();
    float transformMagnitude = transformDifference.Magnitude();
    if (combinedRadius > transformMagnitude)
    {
        DebugPrintF("Collision from sphereObject \n");
        return true ;
    }
    
    return false;
}
    