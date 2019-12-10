#pragma once
#include "Component.h"

GridScript:
public Component
{
	int width;
	int height;

public:
	GridScript(GameObject* gameObject);
	~GridScript();
protected:
	void start();
	void update();
};

