#pragma once
#include "Utils.h"

class GameObject;
class Transform;

class Component {

	GameObject* gameObject;
	Transform* transform;

public:
	Component(GameObject* gameObject);

	virtual ~Component() {};
protected:
	//public으로 생성할 이유 없다. 멤버함수는 소문자, static변수는 대문자.
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDistroy() {}
	//함수 바디를 채워넣지 안는것. 이름 입력파라미터는 만들지만 본체를 만들지 않으면 순수 가상함수 된다.
	//abstract void onDestroy(); //함수의 주소정보를 널로 만든다. 함수에 접근하면 시스템이 죽어버림. 순수 가상함수가 하나라도 있는 클래스는 사용할 수 없다.
	//virtual void onDestroy() = 0; //이렇게 만들고나면 이 함수를 상속받은 클래스는 반드시 함수 바디를 만들어 줘야한다.따라서 
	//	virtual void onDestroy() PURE; MS에서 표기하는 함수 바디가 비어잇다는 표시.
};

class MyScript :public Component //monoBehavior로 생각하면 될듯.
{
protected:
	virtual void start() override;
	virtual void update() override;

};

class Transform :public Component 
{
	//유니티의 트렌스폼에 어떤 기능 있는가
	Vector2 position;
	Vector2 rotation;//쿼터니언.
	Vector2 scale;

public:
	Transform(GameObject* gameObject, const Vector2 & position = Vector2::zero, const Vector2& rotation = Vector2::zero, const Vector2& scale = Vector2::ones)
		: position(position), rotation(rotation), scale(scale), Component(gameObject) {}
protected:
	virtual void start() override;//override할 것. virtual함수를 오버라이드 할 것이라고 선언.
	virtual void update() override;

};