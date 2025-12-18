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