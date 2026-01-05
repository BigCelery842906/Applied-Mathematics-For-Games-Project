#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance) : _type(type), _appearance(appearance)
{
	_parent = nullptr;
	
	_localTransform = new Transform(this);
}

GameObject::~GameObject()
{
	_parent = nullptr;
}

void GameObject::Update()
{
	static int x = 0;

	char sz[1024] = { 0 };

	sprintf_s(sz, "the number is %d \n", x);

	OutputDebugStringA(sz);

	x++;
}