#pragma once
#include <iostream>

using namespace std;

class GameObject;
class Transform;

class Component {
	Transform* transform;

protected:
	GameObject* gameObject;

public:
	Component(GameObject* gameObject);

	virtual ~Component();

protected:
	friend class GameObject;
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void fixedUpdate() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDestroy() {}
};
