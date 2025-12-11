#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Transform.h"

using namespace DirectX;
using namespace std;

struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
};

class GameObject
{
public:
	GameObject(string type, Geometry geometry, Material material, Transform* transform);
	~GameObject();

	string GetType() const { return _type; }

	void SetParent(GameObject * parent) { _parent = parent; }

	


	// Rendering information
	Geometry GetGeometryData() const { return _geometry; }
	Material GetMaterial() const { return _material; }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &_textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void Update(float dt);
	void Move(XMFLOAT3 direction);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	GameObject* _parent = nullptr;
	Transform* _localTransform = nullptr;
	
	string _type;
	XMFLOAT4X4 _world;

	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView* _textureRV = nullptr;
	
	
};

