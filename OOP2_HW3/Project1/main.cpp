#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>


class Screen
{
	int width;
	int height;
	char* canvas;

	static Screen* instance;
	Screen(int width = 30, int height = 20)
		: width(width), height(height),
		canvas(new char[width *height + 1])
	{
		srand(unsigned int(time(0)));
	}

public:
	static Screen& getInstance() {
		if (instance == nullptr) {
			instance = new Screen();
		}
		// 반환형이 Screen&이므로 반환을 해야한다. 객체 자체를 반환하는것같지만 레퍼런스형(포인터랑비슷)을 반환한다.
		return *instance; // 포인터에 접근해서 객체의 레퍼런스형을 반환
	}

	~Screen() {
		if (instance) {
			delete[] canvas;
			instance = nullptr;
		}
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }


	void render()
	{
		char* drawPoint = &(canvas[0]);
		for (int i = 0; i < height; ++i)
		{
			printf("%.*s\n", width, drawPoint);
			drawPoint += width;
		}
	}

	void draw(int x, int y, char shape)
	{
		if (false == checkMove(x, y))
		{
			return;
		}
		canvas[width *y + x] = shape;
	}

	void clear()
	{
		system("cls");
	}

	void initWithItem()
	{
		memset(canvas, 'O', width*height);
		canvas[width*height] = '\0';
	}

	void removeItem(int x, int y)
	{
		if (false == checkMove(x, y))
		{
			return;
		}
		canvas[width *y + x] = '.';
	}

	bool checkMove(int x, int y)
	{
		if (x < 0 || x >= width ||
			y < 0 || y >= height)
		{
			return false;
		}

		return true;
	}
};


class Monster
{
	char shape;
	int x;
	int y;
public:
	Monster()
		: shape('X')
	{
		x = rand() % (Screen::getInstance().getWidth());
		y = rand() % (Screen::getInstance().getWidth());
	}

	void update()
	{
		randomMove();
		Screen::getInstance().draw(x, y, shape);
	}

	void randomMove()
	{
		// -1 0 1 중에 하나 나온다
		int random1 = (rand() % 3) - 1;
		int random2 = (rand() % 3) - 1;

		// 갈수 있을때 까지 뽑는다
		while (false == Screen::getInstance().checkMove(x + random1, y + random2))
		{
			random1 = (rand() % 3) - 1;
			random2 = (rand() % 3) - 1;
		}

		Screen::getInstance().removeItem(x, y);

		x += random1;
		y += random2;

		Screen::getInstance().removeItem(x, y);
	}


};

Screen* Screen::instance = nullptr;


int main()
{
	// 게임루프

	Screen & screen = Screen::getInstance();
	screen.initWithItem();
	Monster monster1;
	while (true)
	{
		// 지우고
		screen.clear();

		monster1.update();
		// 다시 그려준다.
		screen.render();

		Sleep(20);
	}
	return 0;
}