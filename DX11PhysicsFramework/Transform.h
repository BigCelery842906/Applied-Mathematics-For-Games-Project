#pragma once
#include <directxmath.h>
#include "Quaternion.h"

using namespace DirectX;

class GameObject;

class Transform
{
private:
    Vector3 _position;
    Quaternion _orientation;
    Vector3 _scale;
    
    XMFLOAT4X4 _world;
    
    Transform* _parentGO = nullptr;
public:
    
    // Setters and Getters for position/rotation/scale
    //Position
    void SetPosition(Vector3 position) { _position = position; }
    void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

    Vector3 GetPosition() const { return _position; }

    //Scale
    void SetScale(Vector3 scale) { _scale = scale; }
    void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

    Vector3 GetScale() const { return _scale; }

    //Rotation
    void SetRotation(float x, float y, float z) { _orientation = MakeQFromEulerAngles(x, y, z); }
    void SetRotation(Vector3 rotation) { _orientation = MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z); }
    
    Vector3 GetRotation() const { return MakeEulerAnglesFromQ(_orientation); }
    
    //Orientation
    void SetOrientation(Quaternion newOrientation) { _orientation = newOrientation; }
    
    Quaternion GetOrientation() const { return _orientation; }

    //World Matrix
    void SetWorldMatrix(XMMATRIX world) { XMStoreFloat4x4(&_world, world); }
   
    XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

    //Standard Functions
    Transform(GameObject* parentGO);
    ~Transform();
    void Update(float dt);
    void Move(XMFLOAT3 direction);
};
