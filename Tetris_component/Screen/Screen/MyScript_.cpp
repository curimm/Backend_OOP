#include "MyScript_.h"
#include "GameObject.h"
#include "Component.h"

using namespace std;

MyScript::MyScript(GameObject* gameObject)
	: Component(gameObject)
{}

MyScript_::~MyScript_()
{
}
