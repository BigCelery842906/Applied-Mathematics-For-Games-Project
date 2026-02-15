#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

bool PlaneCollider::CollidesWith(SphereCollider& other)
{
    Vector3 planePoint = GetPosition();
    
    Vector3 sphereCenter = other.GetPosition();
    float sphereRadius = other.GetRadius();
    
    //Get the local plane 'up'
    //Check whether the sphere is within the radius of the plane up
    // Then check to see whether the other two axes are within range
    
    Vector3 rotation = _transform->GetRotation();
    Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 up = Vector3(rotation.x * worldUp.x, rotation.y * worldUp.y, rotation.z * worldUp.z);
    
    Vector3 differenceInPosition = planePoint - sphereCenter;
    if (differenceInPosition.Magnitude() < sphereRadius)
    {
        return true;
    }
    
    
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
