#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(const string& name, GameObject* parent, const string& tag)
	: name(name), tag(tag), enabled(true), parent(parent), transform(new Transform(this))
{
	componenets.clear();
	componenets.push_back(transform);
}

GameObject::~GameObject()
{

}

Transform* GameObject::getTransform()
{
	return transform;
}

void GameObject::setParent(GameObject* parent)
{
	this->parent = parent;
}

GameObject* GameObject::Find(const string& path)
{
}


bool GameObject::isActive()
{
	return enabled;
}

void GameObject::setActive(bool flag = true)
{
	enabled = flag;
}