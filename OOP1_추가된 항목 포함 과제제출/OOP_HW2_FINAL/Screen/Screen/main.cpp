// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cmath>

using namespace std;

int countOfEnemyKilled = 0;

//void draw(char* loc, const char* face)
//{
//	strncpy(loc, face, strlen(face));
//}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) {}
	~Screen() 
	{ 
		if(screen!=nullptr)
			delete[] screen;
	}

	void draw(int pos, const char* face) 
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render()
	{
		screen[size - 1] = '\0';
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

	bool isOutOfScreen(int pos)
	{
		return (pos < 0 || pos >= size);
	}

};

class GameObject 
{
private:

	int pos;
	char face[20];
	Screen& screen;
	float hp;

public:
	GameObject(int pos, const char* face, Screen& screen, float hp)
		: pos(pos), screen(screen), hp(hp)
	{
		strcpy(this->face, face);
		//this->hp = hp;
	}

	 virtual void update() {}

	void setFace(const char * face)
	{
		if (face == nullptr) return;
		strcpy(this->face, face);
	}

	int getPosition()
	{
		return pos;
	}

	void setPosition(int pos)
	{
		this->pos = pos;
	}
	virtual void draw()
	{
		if (isAlive() == false) return;
		screen.draw(pos, face);
	}
	bool isAlive()
	{
		return hp > 0;
	}

	void decreaseHp(float value)
	{
		if (value <= 0) return;
		hp -= value;
	}

	void increaseHp(float value)
	{
		if (value <= 0) return;
		hp += value;
	}

	void setHp(float value)
	{
		if (value < 0) return;
		hp = value;
	}

	//Screen * getScreen() { return screen; }
	bool isOutOfScreen(int pos) { return screen.isOutOfScreen(pos); }
};

class Player : public GameObject 
{
private:
	// �����϶� false / �������϶� true
	bool direction;
	
public:
	Player(int pos, const char* face, Screen& screen) 
		: GameObject(pos, face, screen,10), direction(false)
	{	

	}

	bool getDirection()
	{
		return direction;
	}
	
	void moveLeft()
	{
		direction = false;
		setPosition(getPosition() - 1);
		setFace("-o.o)");
		// �θ�Ŭ������ private��������� �ٷ��������� ���Ѵ�.
		//strcpy(face, "(^_^-");
	}

	void moveRight()
	{
		direction = true;
		setPosition(getPosition() + 1);
		setFace("(o.o-");
	}

	virtual void update()
	{
		if (isAlive() == false) return;
	}

};

class Enemy : public GameObject {
	
private:
	Player * target;
	int currentMoveFrame;
	int moveFrame;
	float power;
public:
	Enemy(int pos, const char* face, Player * target, Screen& screen)
		: GameObject(pos, face, screen,5), target(target), currentMoveFrame(0), moveFrame(60), power(2.0/30.0)
	{
	}

	void moveRandom()
	{
		setPosition( getPosition() + rand() % 3 - 1);
	}

	void moveToTarget()
	{
		if (target == nullptr) return;
		int targetPos = target->getPosition();
		int pos = getPosition();
		if (targetPos > pos)
		{
			setPosition(pos + 1);
		}
		else if (targetPos < pos)
		{
			setPosition(pos - 1);
		}
		

	}


	virtual void update()
	{
		if (isAlive() == false) return;

		if (abs(target->getPosition() - getPosition()) <= 5)
		{
			// �÷��̾��� hp����
			target->decreaseHp(power);

		}

		// 2�ʰ� �����ٸ� �̵�
		++currentMoveFrame;
		if (currentMoveFrame < 60) return;

		//moveRandom();
		moveToTarget();
		currentMoveFrame = 0;
	}

	void resetAllInfo(Player * target, int pos = 30)
	{
		setHp(5);
		setPosition(pos);
		currentMoveFrame = 0;
		this->target = target;
	}
};

class Bullet : public GameObject {
	bool isFiring;
	bool direction;
	//Enemy * target;
	Enemy * targetEnemies;
	int countOfEnemies;
	float power;
public:
	Bullet(int pos, const char* face, Enemy * targetEnemies,  int countOfEnemies, Screen& screen)
		: GameObject(pos, face, screen, 1), targetEnemies(targetEnemies), countOfEnemies(countOfEnemies), isFiring(false), direction(false), power(1)
	{
	}

	bool getIsFiring() { return isFiring; }

	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	virtual void draw()
	{
		if (isFiring == false) return;
		GameObject::draw();
	}

	void fire(int player_pos, bool direction, Enemy * target)
	{
		isFiring = true;
		this->direction = direction;
		setPosition(player_pos);
	}

	virtual void update(/*int enemy_pos*/)
	{
		if (isFiring == false) return;

		int pos = getPosition();
		// ��ũ�� �ٱ����� �������쵵 isFiring�� false�� ���ش�.
		if (isOutOfScreen(pos))
		{
			isFiring = false;
			//target = nullptr;
			return;
		}

		// ���� �¾��� ��� // ���� ���� �ִ� ��쿡 ����ġ���� �񱳸� ���ش�.
		if (targetEnemies != nullptr)
		{
			// ���� ����� ���� ã�Ƽ� �¾Ҵ��� Ȯ��
			int target = -1;
			int distance = -1; 
			
			for (int i = 0; i < countOfEnemies; ++i)
			{
				if (targetEnemies[i].isAlive() == false) continue;
				
				int currentDistance = abs(targetEnemies[i].getPosition() - getPosition());

				if (distance == -1)
				{
					distance = currentDistance;
					target = i;
					continue;
				}

				if (distance > currentDistance)
				{
					distance = currentDistance;
					target = i;
				}
			}

			if (target != -1)
			{
				int enemy_pos = targetEnemies[target].getPosition();
				if (pos == enemy_pos)
				{
					isFiring = false;
					targetEnemies[target].decreaseHp(power);

					if (targetEnemies[target].isAlive() == false)
					{
						++countOfEnemyKilled;
					}
					return;
				}
			}


		}

		int value = 0;
		if (direction == true) value = 1;
		else value = -1;
		setPosition(pos + value);

		//int pos = getPosition();
		//if (pos < enemy_pos) {
		//	pos = pos + 1;
		//}
		//else if (pos > enemy_pos) {
		//	pos = pos - 1;
		//}
		//else // �¾��� ���
		//{
		//	// ���� ü���� ���ҽ�Ų��.
		//	isFiring = false;
		//}
		//setPosition(pos);
	}
};

int main()
{
	int countOfEnemies = 5;
	int countOfBullets = 10;
	Screen screen{ 80 };



	Player player = { 30, "-o.o)", screen };

	Enemy enemies[5]
	{
		{50, "(+_+)", &player, screen },
		{55, "(+_+)", &player, screen },
		{60, "(+_+)", &player, screen },
		{65, "(+_+)", &player, screen },
		{40, "(+_+)", &player, screen },

	};


	Bullet bullets[10]
	{
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen},
		{-1, "+", enemies, countOfEnemies, screen}
	};


	GameObject * gameObjects[] =
	{
		&player,

		&enemies[0],
		&enemies[1],
		&enemies[2],
		&enemies[3],
		&enemies[4],

		&bullets[0],
		&bullets[1],
		&bullets[2],
		&bullets[3],
		&bullets[4],
		&bullets[5],
		&bullets[6],
		&bullets[7],
		&bullets[8],
		&bullets[9],
	};
	const int enemySpawnFrame = 300;
	int currentEnemySpawnFrame = 0;

	while (true)
	{
		screen.clear();

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				int i = 0;
				for (; i < countOfBullets; ++i)
				{
					if (bullets[i].getIsFiring() == false)
					{
						break;
					}
				}

				if (i != countOfBullets)
				{
					bullets[i].fire(player.getPosition(), player.getDirection(), enemies);
				}

				break;
			}
		}

		// ���࿡ ���� ��Ÿ���� ���� / enemy�� 5������ �ƴҶ� ����
		if (currentEnemySpawnFrame >= enemySpawnFrame)
		{
			for (int i = 0; i < countOfEnemies; ++i)
			{
				if (enemies[i].isAlive() == false)
				{
					enemies[i].resetAllInfo(&player);
					currentEnemySpawnFrame = 0;
					break;

				}
			}
		}
		else
		{
			currentEnemySpawnFrame++;
		}

		// ��� ������Ʈ���� ������Ʈ ���ش�
		for (int i = 0; i < 16; ++i)
		{
			if (gameObjects[i] == nullptr) continue;
			gameObjects[i]->update();
		}

		//player.update();
		//for (int i = 0; i < countOfEnemies; ++i)
		//{
		//	enemies[i].update();
		//}
		//for (int i = 0; i < countOfBullets; ++i)
		//{
		//	bullets[i].update(/*enemies[targetEnemy].getPosition()*/);
		//}


		for (int i = 0; i < 16; ++i)
		{
			if (gameObjects[i] == nullptr) continue;
			gameObjects[i]->draw();
		}
		// ��� ������Ʈ���� ��ũ���� �׸���.
		//player.draw();
		//for (int i = 0; i < countOfEnemies; ++i)
		//{
		//	enemies[i].draw();
		//}
		//for (int i = 0; i < countOfBullets; ++i)
		//{
		//	bullets[i].draw();
		//}


		// ���������� ȭ���� �׷��ش�
		screen.render();


		// �÷��̾ �׾����� ó��


		Player * pP = nullptr;

		for (int i = 0; i < 16; ++i)
		{
			pP = dynamic_cast<Player *>(gameObjects[i]);
			if (pP == nullptr) continue;

			break;
		}

		if (pP != nullptr)
		{
			if (pP->isAlive() == false)
			{
				cout << "player is dead / countOfEnemyKilled is " << countOfEnemyKilled << endl;
				break;
			}
		}


		Sleep(66);
	}

	return 0;
}