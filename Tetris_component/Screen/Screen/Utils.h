//컴파일하면서 GameEngine에서 util이 두번 호출된다. 메인.obj에서도,메인.obj 둘다에 유틸의 스테틱변수가 들어있음.
//소스코드에 분리해서 넣으면 헤더파일에 선언만 해두고 소스는 소스코드 안에 있다. 이 것 때문에 소스코드를 분리하느 것이다.(전방위 선언때문에)
//#ifndef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#endif // !_CRT_SECURE_NO_WARNINGS전처리 됬는지 확인하게 함.

#ifndef UTILS_H_
#define UTILS_H_
#include <cstdio>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring>
#include <string.h>

//컴파일할때 소스코드를 컴파일 하기 위해서 헤더파일이 컴파일된 것 처럼 보일 뿐이다.
//그래서 util에서도 _CRT_SECURE_NO_WARNINGS 다시 넣어줘야 한다.
using namespace std;

struct Vector2
{
	float x;
	float y;
	const int X() const { return (int)x; }
	const int Y() const { return (int)y; }
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}
	Vector2(const Vector2& other) : Vector2(other.x, other.y) {}

	static Vector2 zero;
	static Vector2 ones;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;

	//x,y는 float니까 제곱하면 더블일 수 있음.
	float magnitude() {
		return sqrt(this->sqrtMagnitude());

	}
	//변수와 비슷한 함수들의 집합이다. 겉보기에는 변수처럼 보임.  매그니투드를 변수로 쓰는 것이 적합하지 않기 때문에 함수로쓴다.

	double sqrtMagnitude() {
		return (double)x*x + y * y;//x,y는 float니까 제곱하면 더블일 수 있음.
	}

	Vector2 operator-(const Vector2& other)
	{
		return { this->x - other.x, this->y - other.y };
	}

	static friend Vector2 operator-(Vector2& a, const Vector2& b);
	//글로벌 이라고 표현할 때 네임스페이스 생략하고. strcpy라고 쓸 때 앞에 ::생략 하는 것이다.
	static friend double Distance(Vector2& a, const Vector2& b);

	Vector2 operator+(const Vector2& other) {
		return { this->x + other.x, this->y + other.y };
	}
	bool operator==(const Vector2& other) {
		return (x == other.x && y == other.y);
	}

	Vector2& operator+=(const Vector2& other) {
		x += other.x, y += other.y;
		return *this;
	}

	static friend Vector2 operator-(const Vector2& a, const Vector2& b);

};


//
//Vector2 Vector2::zero{ 0, 0};
//Vector2 Vector2::ones{ 1, 1 };
//Vector2 Vector2::up{ 0, 1 };
//Vector2 Vector2::down{ 0, -1 };
//Vector2 Vector2::left{ -1, 0 };
//Vector2 Vector2::right{ 1, 0 };
//
//Vector2 operator-(Vector2& a, const Vector2& b)
//{	
//	return (a.operator-(b));
//}
//
//double :: Distance(Vector2& a, const Vector2& b)
//{
//	return (a.operator-(b)).magnitude();
//}
//::strcpy앞에 글로벌 스코어를 설명하는 것이라고 생각하면 된다.




enum class KeyCode {
	Space = 0,
	Left,
	Right,
	Up,
	Down,

	Esc,
	Enter,

	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

//static vector<WORD> keyCodeTable{
//	VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
//	VK_ESCAPE, VK_RETURN, 
//	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
//	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
//};


class Input {
	static INPUT_RECORD InputRecord[128];
	static DWORD Events;
	static bool evaluated;
	static bool gotMouseEvent;
	static bool gotKeyEvent;
	static Position mousePosition;
	static WORD vKeyCode;

	

public:

	static void EndOfFrame();
	/*{
		evaluated = false;
		gotMouseEvent = false;
		gotKeyEvent = false;
	}*/

	static void Initialize()
	{

		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

		EndOfFrame();
	}
	static bool GetMouseEvent(Vector2& pos);

	static bool GetKeyEvent(WORD& keyCode);

	static bool GetKeyDown(KeyCode key);
};



class Borland {

public:


	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Vector2* pos)
	{
		if (!pos) return;
		gotoxy((*pos).X(), (*pos).Y());
	}
	static void gotoxy(const Vector2& pos)
	{
		gotoxy(pos.X(), pos.Y());
	}
};

class Screen {
	int width;
	int height;
	char* canvas;

	static Screen* instance;
	Screen(int width = 90, int height = 50)
		: width(width), height(height),
		canvas(new char[(width + 1)*height])

	{
		Input::Initialize();
	}
public:
	static Screen& getInstance() {
		if (instance == nullptr) {
			instance = new Screen();
		}
		return *instance;
	}

	~Screen() {
		if (instance) {
			delete[] canvas;
			instance = nullptr;
		}
	}

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	void drawRect(const Vector2& pos, int w, int h)
	{
		canvas[pos.X()] = '\xDA';
		canvas[pos.X() + w - 1] = '\xBF';
		memset(&canvas[pos.X() + 1], '\xC4', w - 2);
		canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1)] = '\xC0';
		canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1) + w - 1] = '\xD9';
		memset(&canvas[pos.X() + 1 + (pos.Y() + (h - 1))*(width + 1)], '\xC4', w - 2);
		for (int i = 1; i < h - 1; i++) {
			canvas[pos.X() + (pos.Y() + i)*(width + 1)] = '\xB3';
			canvas[pos.X() + w - 1 + (pos.Y() + i)*(width + 1)] = '\xB3';
		}
	}

	void draw(const char* shape, int w, int h, const Vector2& pos)
	{
		if (!shape) return;
		for (int i = 0; i < h; i++)
		{//safe버전이 필요한 이유(SECURE_NO_WARNINGS그거): 버퍼 오버플로우문제 때문에. 파라미터가 들어가는데 포인터변수만 들어가서 
			//널로 끝나지 않는 주소를 보내줬을 때, 버퍼공간이 입력된 포인터에 대해서 얼마나 큰지 모르기 때문에 이 값들을 잃을 수 있따.
			//입력파라미터는 어떤 것이든 들어갈 수 있다.RETURN주소 넣다보면 널값으로 안끝났을 때, 해당하는 범위를 벗어나 리턴 주소까지 건드려 버린다.
			//최대 버퍼사이즈가 얼마인지 미리 명시해주는 것.
			strncpy(&canvas[pos.X() + (pos.Y() + i)*(width + 1)], &shape[i*w], w);
		}
	}

	void render()
	{
		for (int i = 0; i < height; i++)
			canvas[width + i * (width + 1)] = '\n';
		canvas[width + (height - 1) * (width + 1)] = '\0';
		Borland::gotoxy(0, 0);
		std::cout << canvas;
	}

	void clear()
	{
		memset(canvas, ' ', (width + 1)*height);
		canvas[width + (height - 1)*(width + 1)] = '\0';
	}
};



#endif 

