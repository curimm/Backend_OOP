#pragma once
#include <iostream>
#include <string>
#include<vector>
#include"Utils.h"


using namespace std;

class Component;
class Transform;

class GameObject {
	bool		enabled;
	string		name;
	string		tag;
	GameObject* parent;
	vector<Component *> components;

	vector<GameObject *> children; //변수 명에 단수/복수 확실히 해야한다.한글변수명 안된다.

	static vector<GameObject *> gameObjects;
	friend class GameEngine;

	Transform* transform;

public:
	GameObject(const string& name,
		GameObject* parent = nullptr,
		const string& tag = "",
		GameObject* gameObject,
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones
	);

	~GameObject();
	tamplate<typename T>
		void addComponent();
	getComponent();

	void traverseStart();
	void traverseUpdate();

	//	void traverse();

	Transform* getTransform() { return transform; }

	static GameObject* Find(const string& path);

	void setParent(GameObject* parent)
	{
		this->parent = parent;
	}

	virtual bool isActive()
	{
		return enabled;
	}

	void setActive(bool flag = true)
	{
		enabled = flag;
	}

};
