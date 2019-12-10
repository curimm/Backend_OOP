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

using namespace std;

class GameObject;
class Component;
class Transform;

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
	GameEngine& engine = GameEngine::getInstance();

	engine.mainLoop();

	return 0;
}