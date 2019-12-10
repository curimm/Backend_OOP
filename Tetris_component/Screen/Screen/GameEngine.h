#pragma once
#include <iostream>
#include <string>

using namespace std;

class Screen;
class Input;

class GameEngine {
	Screen& screen;

	static GameEngine* instance;

	GameEngine();

public:
	static GameEngine& getInstance();

	void mainLoop();
};

