//�������ϸ鼭 GameEngine���� util�� �ι� ȣ��ȴ�. ����.obj������,����.obj �Ѵٿ� ��ƿ�� ����ƽ������ �������.
//�ҽ��ڵ忡 �и��ؼ� ������ ������Ͽ� ���� �صΰ� �ҽ��� �ҽ��ڵ� �ȿ� �ִ�. �� �� ������ �ҽ��ڵ带 �и��ϴ� ���̴�.(������ ���𶧹���)
//#ifndef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#endif // !_CRT_SECURE_NO_WARNINGS��ó�� ����� Ȯ���ϰ� ��.

#ifndef UTILS_H_
#define UTILS_H_
#include <cstdio>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring>
#include <string.h>

//�������Ҷ� �ҽ��ڵ带 ������ �ϱ� ���ؼ� ��������� �����ϵ� �� ó�� ���� ���̴�.
//�׷��� util������ _CRT_SECURE_NO_WARNINGS �ٽ� �־���� �Ѵ�.
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

	//x,y�� float�ϱ� �����ϸ� ������ �� ����.
	float magnitude() {
		return sqrt(this->sqrtMagnitude());

	}
	//������ ����� �Լ����� �����̴�. �Ѻ��⿡�� ����ó�� ����.  �ű״����带 ������ ���� ���� �������� �ʱ� ������ �Լ��ξ���.

	double sqrtMagnitude() {
		return (double)x*x + y * y;//x,y�� float�ϱ� �����ϸ� ������ �� ����.
	}

	Vector2 operator-(const Vector2& other)
	{
		return { this->x - other.x, this->y - other.y };
	}

	static friend Vector2 operator-(Vector2& a, const Vector2& b);
	//�۷ι� �̶�� ǥ���� �� ���ӽ����̽� �����ϰ�. strcpy��� �� �� �տ� ::���� �ϴ� ���̴�.
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
//::strcpy�տ� �۷ι� ���ھ �����ϴ� ���̶�� �����ϸ� �ȴ�.




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
		{//safe������ �ʿ��� ����(SECURE_NO_WARNINGS�װ�): ���� �����÷ο칮�� ������. �Ķ���Ͱ� ���µ� �����ͺ����� ���� 
			//�η� ������ �ʴ� �ּҸ� �������� ��, ���۰����� �Էµ� �����Ϳ� ���ؼ� �󸶳� ū�� �𸣱� ������ �� ������ ���� �� �ֵ�.
			//�Է��Ķ���ʹ� � ���̵� �� �� �ִ�.RETURN�ּ� �ִٺ��� �ΰ����� �ȳ����� ��, �ش��ϴ� ������ ��� ���� �ּұ��� �ǵ�� ������.
			//�ִ� ���ۻ���� ������ �̸� ������ִ� ��.
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

