// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//추상클래스:추상적 표현들(실체로 만들 수 없는 것들)->클래스로 만들고 생성자 함수 못만들게 하고싶음.(실체화 못하게 하기위해서) 어떻게 만들 것인가
//생성자 함수 호출 못하게 하는 방법:singleton 이용? abstract 키워드.순수 가상함수를 만들면 된다."pure virtual function".
//순수 가상함수를 만들면 된다."pure virtual function".
//함수를 선언할때, 함수이름, 입력파라미터 선언하는데 함수 바디를 만든다. 이때 함수 바디를 만들지 않으면 순수 가상함수 만들어짐.
//virtual은 오버라이딩을 위해 존재.
//
//구현 = implement
//순수 가상함수가 하나라도 잇는것은 생성자 함수를 호출하지 못하게 한다.
//abstract method로만 이루어 진 것 : 인터페이스. c#에는 인터페이스라는 키워드가 존재한다. 따로 인터페이스나 abstract class같은 키워드 없다.
//implenment: 함수 바디를 채우는 것.
//멤버함수를 만드는 것은 virtual 함수를 먼저 만들ㅇ야 한다. 밑에서 오버라이드 안할꺼면 non_virtualrtual로 한다. 디폴트가 virtual!(java가 이렇게 되어잇음.)
//c#:단일 상속. 부모 클래스 하나이다. c++:다중상속. 부모클래스가 여러개기때문에 부모클래스 이름 써야한다. 원래는 코드  재사용을 위해 생긴 것이다.(그래서 부모클래스 여러개.)
//다중상속 모델:하나의 부모클래스에 여려개의 인터페이스 모델을 구현할때 쓰였다.
//단일 상속이 맞음. 그래서 ㅊ++이후에 나온 언어들은 단일상속 사용.

//vector2, submition 구현하기. 코드 완성하기. 어떤 문제가 발생하는지 해결책을 가지고 수업들어오기.
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