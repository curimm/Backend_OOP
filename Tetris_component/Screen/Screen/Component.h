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
	//public���� ������ ���� ����. ����Լ��� �ҹ���, static������ �빮��.
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDistroy() {}
	//�Լ� �ٵ� ä������ �ȴ°�. �̸� �Է��Ķ���ʹ� �������� ��ü�� ������ ������ ���� �����Լ� �ȴ�.
	//abstract void onDestroy(); //�Լ��� �ּ������� �η� �����. �Լ��� �����ϸ� �ý����� �׾����. ���� �����Լ��� �ϳ��� �ִ� Ŭ������ ����� �� ����.
	//virtual void onDestroy() = 0; //�̷��� ������� �� �Լ��� ��ӹ��� Ŭ������ �ݵ�� �Լ� �ٵ� ����� ����Ѵ�.���� 
	//	virtual void onDestroy() PURE; MS���� ǥ���ϴ� �Լ� �ٵ� ����մٴ� ǥ��.
};

class MyScript :public Component //monoBehavior�� �����ϸ� �ɵ�.
{
protected:
	virtual void start() override;
	virtual void update() override;

};

class Transform :public Component 
{
	//����Ƽ�� Ʈ�������� � ��� �ִ°�
	Vector2 position;
	Vector2 rotation;//���ʹϾ�.
	Vector2 scale;

public:
	Transform(GameObject* gameObject, const Vector2 & position = Vector2::zero, const Vector2& rotation = Vector2::zero, const Vector2& scale = Vector2::ones)
		: position(position), rotation(rotation), scale(scale), Component(gameObject) {}
protected:
	virtual void start() override;//override�� ��. virtual�Լ��� �������̵� �� ���̶�� ����.
	virtual void update() override;

};