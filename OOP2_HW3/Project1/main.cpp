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
		// ��ȯ���� Screen&�̹Ƿ� ��ȯ�� �ؾ��Ѵ�. ��ü ��ü�� ��ȯ�ϴ°Ͱ����� ���۷�����(�����Ͷ����)�� ��ȯ�Ѵ�.
		return *instance; // �����Ϳ� �����ؼ� ��ü�� ���۷������� ��ȯ
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
		// -1 0 1 �߿� �ϳ� ���´�
		int random1 = (rand() % 3) - 1;
		int random2 = (rand() % 3) - 1;

		// ���� ������ ���� �̴´�
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
	// ���ӷ���

	Screen & screen = Screen::getInstance();
	screen.initWithItem();
	Monster monster1;
	while (true)
	{
		// �����
		screen.clear();

		monster1.update();
		// �ٽ� �׷��ش�.
		screen.render();

		Sleep(20);
	}
	return 0;
}