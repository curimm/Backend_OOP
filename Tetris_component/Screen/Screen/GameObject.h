#pragma once
#include <string>
#include<vector>

using namespace std;

class Component;
class Transform;

class GameObject {
	bool enabled;
	string name;
	string tag;
	GameObject* parent;
	vector<Component *> componenets;
	static vector<GameObject *> gameObjects;
	Transform* transform;

public:
	GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "");
	~GameObject();

	Transform* getTransform();
	static GameObject* Find(const string& path);

	void setParent(GameObject* parent);
	virtual bool isActive();
	void setActive(bool flag = true);
};