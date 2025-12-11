#pragma once

#include <directxmath.h>

using namespace DirectX;

class Transform
{
private:
    XMFLOAT3 _position;
    XMFLOAT3 _rotation;
    XMFLOAT3 _scale;
    
    
public:
    
    // Setters and Getters for position/rotation/scale
    //Position
    void SetPosition(XMFLOAT3 position) { _position = position; }
    void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

    XMFLOAT3 GetPosition() const { return _position; }

    //Scale
    void SetScale(XMFLOAT3 scale) { _scale = scale; }
    void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

    XMFLOAT3 GetScale() const { return _scale; }

    //Rotation
    void SetRotation(XMFLOAT3 rotation) { _rotation = rotation; }
    void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

    XMFLOAT3 GetRotation() const { return _rotation; }


    Transform();
    ~Transform();
    void Update();
};
