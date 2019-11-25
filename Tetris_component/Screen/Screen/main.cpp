// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//�߻�Ŭ����:�߻��� ǥ����(��ü�� ���� �� ���� �͵�)->Ŭ������ ����� ������ �Լ� ������� �ϰ����.(��üȭ ���ϰ� �ϱ����ؼ�) ��� ���� ���ΰ�
//������ �Լ� ȣ�� ���ϰ� �ϴ� ���:singleton �̿�? abstract Ű����.���� �����Լ��� ����� �ȴ�."pure virtual function".
//���� �����Լ��� ����� �ȴ�."pure virtual function".
//�Լ��� �����Ҷ�, �Լ��̸�, �Է��Ķ���� �����ϴµ� �Լ� �ٵ� �����. �̶� �Լ� �ٵ� ������ ������ ���� �����Լ� �������.
//virtual�� �������̵��� ���� ����.
//
//���� = implement
//���� �����Լ��� �ϳ��� �մ°��� ������ �Լ��� ȣ������ ���ϰ� �Ѵ�.
//abstract method�θ� �̷�� �� �� : �������̽�. c#���� �������̽���� Ű���尡 �����Ѵ�. ���� �������̽��� abstract class���� Ű���� ����.
//implenment: �Լ� �ٵ� ä��� ��.
//����Լ��� ����� ���� virtual �Լ��� ���� ���餷�� �Ѵ�. �ؿ��� �������̵� ���Ҳ��� non_virtualrtual�� �Ѵ�. ����Ʈ�� virtual!(java�� �̷��� �Ǿ�����.)
//c#:���� ���. �θ� Ŭ���� �ϳ��̴�. c++:���߻��. �θ�Ŭ������ �������⶧���� �θ�Ŭ���� �̸� ����Ѵ�. ������ �ڵ�  ������ ���� ���� ���̴�.(�׷��� �θ�Ŭ���� ������.)
//���߻�� ��:�ϳ��� �θ�Ŭ������ �������� �������̽� ���� �����Ҷ� ������.
//���� ����� ����. �׷��� ��++���Ŀ� ���� ������ ���ϻ�� ���.

//vector2, submition �����ϱ�. �ڵ� �ϼ��ϱ�. � ������ �߻��ϴ��� �ذ�å�� ������ ����������.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include<array>
#include <string>
#include<algorithm>
#include <ctime>
#include "Utils.h"
#include "Component.h"

using namespace std;

class GameObject;
class Components;
class Transform;

class GameObject {
	bool enabled;
	string name;
	string tag;
	GameObject* parent;
	vector<Component *>components;
	static vector<GameObject *>gameObjects;
	Transform* transform;

public:
	GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "")
		: name(name), tag(tag), enabled(true), parent(parent),
		transform(new Transform(this)) {
		components.clear();
		components.push_back(transform);
	}

	~GameObject()
	{
	}

	Transform* getTransform()
	{
		return transform;
	}

	static GameObject* Find(const string& path)
	{
	}

	void setParent(GameObject* parent)
	{
		this->parent = parent;
	}

	virtual bool isActive() { return enabled; }
	void setActive(bool flag = true) { enabled = flag; }

};
/*

		void internalDraw(const Position& inheritedPos = Position{ 0, 0 }) {
			if (!enabled) return;

			draw(inheritedPos);

			for (auto& child : children) child->internalDraw(pos + inheritedPos);
		}

		virtual void draw(const Position& inheritedPos = Position{ 0, 0 }) {
			screen.draw(shape, width, height, pos + inheritedPos);
		}

		void internalUpdate() {
			if (!enabled) return;
			update();
			for (auto& child : children) child->internalUpdate();
		}

		virtual void update() {}
	*/

int main()
{
	Screen&	 screen = Screen::getInstance();

	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");


	screen.clear(); screen.render();

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update		

		// erase in active objects

		// draw

		screen.render();
		Sleep(100);

		Input::EndOfFrame();
	}

	return 0;
}