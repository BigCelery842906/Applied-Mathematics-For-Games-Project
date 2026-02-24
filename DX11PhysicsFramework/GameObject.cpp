#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, float mass) : _appearance(appearance), _type(type)
{
	_parent = nullptr;
	
	_localTransform = new Transform(this);
	
	_PhysicsModel = new RigidBodyModel(_localTransform, mass);
}

GameObject::GameObject(string type, Appearance* appearance, PhysicsModel* physicsModel) : _appearance(appearance), _type(type)
{
	_parent = nullptr;
	
	_localTransform = new Transform(this);
	
	_PhysicsModel = physicsModel;
}

GameObject::~GameObject()
{
	_parent = nullptr;
}

void GameObject::Update(float deltaTime)
{
	if (_PhysicsModel)
	{
		_PhysicsModel->Update(deltaTime);
	}
	if (_localTransform)
	{
		_localTransform->Update(deltaTime);
	}
}

void GameObject::ResetObject()
{
	_localTransform->SetPosition(_localTransform->GetSpawnPosition());
	_PhysicsModel->SetAcceleration(Vector3());
	_PhysicsModel->SetVelocity(Vector3());
}