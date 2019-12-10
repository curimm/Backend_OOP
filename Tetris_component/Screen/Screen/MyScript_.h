#pragma once
#include "Component.h"
class GameObject;


class MyScript_ : public Component
{
public:
	MyScript_(GameObject* gameObject);

protected:
		void start(){}

		void update(){}
//	virtual ~MyScript_();
};

