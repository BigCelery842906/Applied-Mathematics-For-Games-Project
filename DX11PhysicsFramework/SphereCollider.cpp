#include "SphereCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    float combinedRadius = GetRadius() + other.GetRadius();
    Vector3 transformDifference = GetPosition() - other.GetPosition();
    float transformMagnitude = transformDifference.Magnitude();
    if (combinedRadius > transformMagnitude)
    {
        out.collisionNormal = transformDifference;
        out.collisionNormal.Normalize();
        out.contactPointCount = 1;
        out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());
        out.points[0].penetrationDepth = fabs(transformDifference.Magnitude() - combinedRadius);
        
        DebugPrintF("Collision from sphereObject \n");
        return true ;
    }
    return false;
}

bool SphereCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
    return other.CollidesWith(*this, out);
}

bool SphereCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
    return other.CollidesWith(*this, out);
}
    