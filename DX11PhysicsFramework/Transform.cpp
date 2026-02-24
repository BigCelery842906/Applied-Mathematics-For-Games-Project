#include "Transform.h"
#include "GameObject.h"

Transform::Transform(GameObject* parentGO)
{
    _parentGO = parentGO->GetTransform();
    _position = Vector3(0.0f, 0.0f, 0.0f);
    _orientation = Quaternion();
    _scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
    _parentGO = nullptr;
}

void Transform::Move(XMFLOAT3 direction)
{	
    _position.x += direction.x;
    _position.y += direction.y;
    _position.z += direction.z;
}

void Transform::Update(float dt)
{
    // Calculate world matrix
    XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
    
    XMVECTOR vector = XMVectorSet(_orientation.v.x, _orientation.v.y, _orientation.v.z, _orientation.n);
    vector = XMQuaternionNormalize(vector);
    
    XMMATRIX rotation = XMMatrixRotationQuaternion(vector);
        
    XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);
    
    XMStoreFloat4x4(&_world, scale * rotation * translation);

    if (_parentGO != nullptr)
    {
        XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parentGO->GetWorldMatrix());
    }
}