#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Transform.h"
#include "Appearance.h"
#include "Structures.h"
using namespace DirectX;
using namespace std;



class GameObject
{
public:
	GameObject(string type, Appearance* _appearance);
	~GameObject();

	string GetType() const { return _type; }

	Transform* GetTransform() { return _localTransform; }
	Appearance* GetAppearance() { return _appearance; }
	
	void SetParent(GameObject * parent) { _parent = parent; }
	GameObject* GetParent() { return _parent; }

private:
	GameObject* _parent = nullptr;
	Transform* _localTransform = nullptr;
	Appearance* _appearance = nullptr;
	
	string _type;
		
};

