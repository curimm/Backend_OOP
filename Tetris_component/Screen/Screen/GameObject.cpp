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
	transform(new Transform(this, position, rotation, scale)) { //멤버 초기화 리스트라는 것이 호출 될까? 내에서 this 사용해도 문제 없다는 뜻이다.
	//트렌스폼이라고하는 클래스의 생성자 함수를 몰라서 생긴 오류. 전방위 선언을 해서 함수를 사용하려할 때, 함수를 찾을 수 없음. 헤더파일에 선언만 되있을 뿐!!
	//#include"Transform.h"넣어줘야한다.
	components.clear();
	components.push_back(transform);
}

void GameObject::addComponent()
{
	T* newComp = new T(this, 10, 10);
	//if (!loop) return; //포인터 변수니까 잘못넘어올 확률 체크해주기
	//components.push_back(comp);
}
template <typename T>
T* GameObject::getComponent()
{
	for (auto comp : components)
	{//이 컴포넌트가 내가 원하는 자료형인지 확인
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