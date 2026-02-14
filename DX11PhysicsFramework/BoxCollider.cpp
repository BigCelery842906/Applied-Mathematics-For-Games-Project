#include "BoxCollider.h"
#include <iostream>
#include <algorithm>

#include "Structures.h"

bool BoxCollider::CollidesWith(SphereCollider& other, Vector3& poc)
{
    Vector3 ColliderSize = GetColliderSize();
    float otherRadius = other.GetRadius();
    
    Vector3 combinedColliderSize = Vector3((ColliderSize.x + otherRadius), (ColliderSize.y + otherRadius), (ColliderSize.z + otherRadius));
    
    Vector3 position = GetPosition();
    Vector3 otherPosition = other.GetPosition();
    Vector3 positionDifference = position - otherPosition;
    
    Vector3 boxMin = GetPosition() - ColliderSize;
    Vector3 boxMax = GetPosition() + ColliderSize;
    
    Vector3 closestPoint;
    closestPoint.x = Clamp(otherPosition.x ,boxMin.x , boxMax.x );
    closestPoint.y = Clamp(otherPosition.y ,boxMin.y , boxMax.y );
    closestPoint.z = Clamp(otherPosition.z ,boxMin.z , boxMax.z );
    
    float xOverlap = std::abs(positionDifference.x);
    float yOverlap = std::abs(positionDifference.y);
    float zOverlap = std::abs(positionDifference.z);
    
    if (xOverlap < combinedColliderSize.x && yOverlap < combinedColliderSize.y && zOverlap < combinedColliderSize.z)
    {
        DebugPrintF("Box Collision Overlap with Sphere X:%f Y:%f Z:%f \n", xOverlap, yOverlap, zOverlap);
        poc = closestPoint;
        return true;
    }
    
    return false;
}
bool BoxCollider::CollidesWith(BoxCollider& other, Vector3& poc)
{
    Vector3 colliderSize = GetColliderSize();
    Vector3 otherColliderSize = other.GetColliderSize();
    Vector3 combinedColliderSize = colliderSize + otherColliderSize;
    
    Vector3 position = GetPosition();
    Vector3 otherPosition = other.GetPosition();
    Vector3 positionDifference = position - otherPosition;
    
    float xOverlap = abs(positionDifference.x);
    float yOverlap = abs(positionDifference.y);
    float zOverlap = abs(positionDifference.z);
    
    
    

    if (xOverlap < combinedColliderSize.x && yOverlap < combinedColliderSize.y && zOverlap < combinedColliderSize.z)
    {
        DebugPrintF("Box Collision (overlap) X:%f Y:%f Z:%f\n", xOverlap, yOverlap, zOverlap);
        
        Vector3 boxAMin = position - colliderSize;
        Vector3 boxAMax = position + colliderSize;
        Vector3 boxBMin = otherPosition + otherColliderSize;
        Vector3 boxBMax = otherPosition - otherColliderSize;
    
        Vector3 overlapMin = Vector3((std::max)(boxAMin.x, boxBMin.x), (std::max)(boxAMin.y, boxBMin.y), (std::max)(boxAMin.z, boxBMin.z));
        Vector3 overlapMax = Vector3((std::min)(boxAMax.x, boxBMax.x), (std::min)(boxAMax.y, boxBMax.y), (std::min)(boxAMax.z, boxBMax.z));
    
        //Return center of contact
        poc = (overlapMin + overlapMax) * 0.5f;
        
        
        return true;
	}
    
    return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other, Vector3& poc)
{
    return other.CollidesWith(*this, poc);
}
