#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, float mass) : _appearance(appearance), _type(type)
{
	_parent = nullptr;
	
	_localTransform = new Transform(this);
	
	_rigidbodyModel = new RigidBodyModel(_localTransform, mass);
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
}