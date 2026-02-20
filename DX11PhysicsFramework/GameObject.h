#pragma once
#include <directxmath.h>
#include <string>
#include "Transform.h"
#include "Appearance.h"
#include "RigidBodyModel.h"

using namespace DirectX;
using namespace std;

class GameObject
{
private:
	GameObject* _parent = nullptr;
	Transform* _localTransform = nullptr;
	Appearance* _appearance = nullptr;
	PhysicsModel* _PhysicsModel = nullptr;
	
	string _type;
public:
	GameObject(string type, Appearance* _appearance, float mass = 1.0f);
	GameObject(string type, Appearance* _appearance, PhysicsModel* physicsModel);
	~GameObject();
	void Update(float deltaTime);

	string GetType() const { return _type; }

	Transform* GetTransform() { return _localTransform; }
	Appearance* GetAppearance() { return _appearance; }
	PhysicsModel* GetPhysicsModel() { return _PhysicsModel; }
	
	void SetPhysicsModel(PhysicsModel* physicsModel) { _PhysicsModel = physicsModel; } 
	
	void SetParent(GameObject * parent) { _parent = parent; }
	GameObject* GetParent() { return _parent; }
	
	void ResetObject();
};

