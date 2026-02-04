#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance) : _type(type), _appearance(appearance)
{
	_parent = nullptr;
	
	_localTransform = new Transform(this);
	
	_rigidbodyModel = new RigidBodyModel(_localTransform);
}

GameObject::~GameObject()
{
	_parent = nullptr;
}

void GameObject::Update(float deltaTime)
{
	if (_rigidbodyModel)
	{
		_rigidbodyModel->Update(deltaTime);
	}
	if (_localTransform)
	{
		_localTransform->Update(deltaTime);
	}
	// static int x = 0;
	//
	// char sz[1024] = { 0 };
	//
	// sprintf_s(sz, "the number is %d \n", x);
	//
	// OutputDebugStringA(sz);
	//
	// x++;
}