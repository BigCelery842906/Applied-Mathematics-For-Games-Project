#include "SphereCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other, Vector3& poc)
{
    float combinedRadius = GetRadius() + other.GetRadius();
    Vector3 transformDifference = GetPosition() - other.GetPosition();
    float transformMagnitude = transformDifference.Magnitude();
    if (combinedRadius > transformMagnitude)
    {
        DebugPrintF("Collision from sphereObject \n");
        
        //Calculate point of contact
        Vector3 direction = transformDifference;
        direction.Normalize();
        Vector3 pointA = GetPosition() + direction * GetRadius();
        Vector3 pointB = other.GetPosition() - direction * other.GetRadius();
        poc = pointA + pointB * 0.5f;
        
        return true ;
    }
    return false;
}

bool SphereCollider::CollidesWith(BoxCollider& other, Vector3& poc)
{
    return other.CollidesWith(*this, poc);
}

bool SphereCollider::CollidesWith(PlaneCollider& other, Vector3& poc)
{
    return other.CollidesWith(*this, poc);
}
    