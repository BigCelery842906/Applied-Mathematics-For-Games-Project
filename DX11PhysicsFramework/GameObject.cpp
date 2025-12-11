#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material, Transform* transform) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;

	_textureRV = nullptr;
	
	_localTransform = transform;
}

GameObject::~GameObject()
{
	_parent = nullptr;
	_textureRV = nullptr;
	_geometry.indexBuffer = nullptr;
	_geometry.vertexBuffer = nullptr;
}

void GameObject::Update(float dt)
{
	XMFLOAT3 _scale = _localTransform->GetScale();
	XMFLOAT3 _rotation = _localTransform->GetRotation();
	XMFLOAT3 _position = _localTransform->GetPosition();
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Move(XMFLOAT3 direction)
{
	XMFLOAT3 pos = _localTransform->GetPosition(); 
	
	pos.x += direction.x;
	pos.y += direction.y;
	pos.z += direction.z;
	
	_localTransform->SetPosition(pos);
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
