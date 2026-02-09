#include "BoxCollider.h"

bool BoxCollider::CollidesWith(SphereCollider& other)
{
    Vector3 ColliderSize = GetColliderSize();
    float otherRadius = other.GetRadius();
    Vector3 combinedColliderSize = Vector3((ColliderSize.x + otherRadius), (ColliderSize.y + otherRadius), (ColliderSize.z + otherRadius));
    
    Vector3 positionDifference = GetPosition() - other.GetPosition();
    
    float xOverlap = std::abs(positionDifference.x);
    float yOverlap = std::abs(positionDifference.y);
    float zOverlap = std::abs(positionDifference.z);
    
    if (xOverlap < combinedColliderSize.x && yOverlap < combinedColliderSize.y && zOverlap < combinedColliderSize.z)
    {
        DebugPrintF("Box Collision Overlap with Sphere X:%f Y:%f Z:%f \n", xOverlap, yOverlap, zOverlap);
        return true;
    }
    
    return false;
}
bool BoxCollider::CollidesWith(BoxCollider& other)
{
    Vector3 ColliderSize = GetColliderSize();
    Vector3 OtherColliderSize = other.GetColliderSize();
    Vector3 combinedColliderSize = ColliderSize + OtherColliderSize;
    
    Vector3 positionDifference = GetPosition() - other.GetPosition();
    
    float xOverlap = abs(positionDifference.x);
	float yOverlap = abs(positionDifference.y);
	float zOverlap = abs(positionDifference.z);

    if (xOverlap < combinedColliderSize.x && yOverlap < combinedColliderSize.y && zOverlap < combinedColliderSize.z)
    {
        DebugPrintF("Box Collision (overlap) X:%f Y:%f Z:%f\n", xOverlap, yOverlap, zOverlap);
        return true;
	}
    
    return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other)
{
    return other.CollidesWith(*this);
}
