#include "GameObject.h"
#include "Component.h"

vector<GameObject*> GameObject::gameObjects;

GameObject* GameObject::Find(const string& path) {
	return nullptr;
}


GameObject::GameObject(const string& name, GameObject* parent = nullptr, const string& tag,
	const	Vector2& position,
	const	Vector2& rotation,
	const	Vector2& scale)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this, position, rotation, scale)) { //��� �ʱ�ȭ ����Ʈ��� ���� ȣ�� �ɱ�? ������ this ����ص� ���� ���ٴ� ���̴�.
	//Ʈ�������̶���ϴ� Ŭ������ ������ �Լ��� ���� ���� ����. ������ ������ �ؼ� �Լ��� ����Ϸ��� ��, �Լ��� ã�� �� ����. ������Ͽ� ���� ������ ��!!
	//#include"Transform.h"�־�����Ѵ�.
	components.clear();
	components.push_back(transform);
}

void GameObject::addComponent()
{
	T* newComp = new T(this, 10, 10);
	//if (!loop) return; //������ �����ϱ� �߸��Ѿ�� Ȯ�� üũ���ֱ�
	//components.push_back(comp);
}
template <typename T>
T* GameObject::getComponent()
{
	for (auto comp : components)
	{//�� ������Ʈ�� ���� ���ϴ� �ڷ������� Ȯ��
		if (dynamic_cast<T *(comp)) {
			return static_cast<T *>(comp);
		}
	}
	return nullptr;
}


void GameObject::traverseStart() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	for (auto child : children)
	{
		child->traverseStart();
	}
}

void GameObject::traverseUpdate() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->update();
	}
	for (auto child : children)
	{
		child->traverseUpdate();
	}
}