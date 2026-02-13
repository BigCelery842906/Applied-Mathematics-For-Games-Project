#include "BoxCollider.h"

#include <algorithm>

bool BoxCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    // Get Collider Sizes
    Vector3 ColliderSize = GetColliderSize();
    float otherRadius = other.GetRadius();
    Vector3 combinedColliderSize = Vector3((ColliderSize.x + otherRadius), (ColliderSize.y + otherRadius), (ColliderSize.z + otherRadius));
    
    // Get Positional Differences, and get absolute values of these
    Vector3 positionDifference = GetPosition() - other.GetPosition();
    float absXDiff = std::abs(positionDifference.x);
    float absYDiff = std::abs(positionDifference.y);
    float absZDiff = std::abs(positionDifference.z);
    
    // If collision is occuring on any axis
    if (absXDiff < combinedColliderSize.x && absYDiff < combinedColliderSize.y && absZDiff < combinedColliderSize.z)
    {
        out.collisionNormal = positionDifference;
        // out.collisionNormal.Normalize();
        out.contactPointCount = 1;
        Vector3 contactPoint;
        contactPoint.x = out.collisionNormal.x * ColliderSize.x;
        contactPoint.y = out.collisionNormal.y * ColliderSize.y;
        contactPoint.z = out.collisionNormal.z * ColliderSize.z;
        
        out.points[0].position = GetPosition() + contactPoint;
        
        // Calculate the overlap between the two objects
        float overlapX = (ColliderSize.x + otherRadius) - absXDiff;
        float overlapY = (ColliderSize.y + otherRadius) - absYDiff;
        float overlapZ = (ColliderSize.z + otherRadius) - absZDiff;
        
        // Find the axis of minimum overlap
        float minOverlap = overlapX; // Assume x is smallest first
        minOverlap = (std::min)(overlapY, minOverlap);
        minOverlap = (std::min)(overlapZ, minOverlap);

        out.points[0].penetrationDepth = minOverlap;
        
        DebugPrintF("Box Collision Overlap with Sphere X:%f Y:%f Z:%f \n", absXDiff, absYDiff, absZDiff);
        return true;
    }
    
    return false;
}
bool BoxCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
    // Get Collider Sizes for both objects
    Vector3 ColliderSize = GetColliderSize();
    Vector3 OtherColliderSize = other.GetColliderSize();
    Vector3 combinedColliderSize = ColliderSize + OtherColliderSize;
    
    // Get Positional Differences, and get absolute values of these
    Vector3 positionDifference = GetPosition() - other.GetPosition();
    float absXDiff = std::abs(positionDifference.x);
    float absYDiff = std::abs(positionDifference.y);
    float absZDiff = std::abs(positionDifference.z);

    if (absXDiff < combinedColliderSize.x && absYDiff < combinedColliderSize.y && absZDiff < combinedColliderSize.z)
    {
        out.collisionNormal = positionDifference;
        out.collisionNormal.Normalize();
        out.contactPointCount = 1;
        Vector3 contactPoint;
        contactPoint.x = out.collisionNormal.x * ColliderSize.x;
        contactPoint.y = out.collisionNormal.y * ColliderSize.y;
        contactPoint.z = out.collisionNormal.z * ColliderSize.z;
        
        out.points[0].position = GetPosition() + contactPoint;
        
        float overlapX = (ColliderSize.x + (OtherColliderSize).x) - absXDiff;
        float overlapY = (ColliderSize.y + (OtherColliderSize).y) - absYDiff;
        float overlapZ = (ColliderSize.z + (OtherColliderSize).z) - absZDiff;
        
        // Find the axis of minimum overlap
        float minOverlap = overlapX; // Assume x is smallest first
        minOverlap = (std::min)(overlapY, minOverlap);
        minOverlap = (std::min)(overlapZ, minOverlap);

        out.points[0].penetrationDepth = minOverlap;
        
        DebugPrintF("Box Collision (overlap) X:%f Y:%f Z:%f\n", absXDiff, absYDiff, absZDiff);
        return true;
	}
    
    return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
    return other.CollidesWith(*this, out);
}
