#include "GameEngine.h"


#include "GameEngine.h"
#include "GameObject.h"
#include "Utils.h"
#include "GridScript.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}


GameEngine::GameEngine()
	: screen(Screen::getInstance()) {
	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");
	screen.clear(); screen.render();
}

void GameEngine::mainLoop() {
	//loop���ư��� ���� ���ʱ�ȭ �����ٶ� �߰��ϱ�.
	GameObject map("Map");//map���� �����.�������� grid������ ���� ������ �־������
	auto& objs = GameObject::gameObjects;
	//& objs �Ⱦ��� ���� ��ü�� �ִµ� �װŸ� �� �����ؼ� ����ϴ� ��.
	const int maxFoods = 10;

	map.addComponent<GridScript>();
	GridScript* comp = map.getComponent<GridScript>();



	GridScript grid(&map, 40, 40);
	//map.components.push_back(&grid);
	//�̰� ���ӿ����̴ϱ� friends���� ������ �ߴ� ���̴�.�ȿ� ������ �� �ִ� ����� �ϳ�. ����Ƽ������ addComponents,getComponents�� ���� ���̴�.
	//��� Ŭ������ �ִ� �Լ��ΰ�?���ӿ�����Ʈ���� ��û�ؾ��ϴ� ���׵�. = ��ü
	//addComp ������
	map.addComponent<GridScript>();
	GridScript* comp = map.getComponent<GridScript>();

	for (int i = 0; i < maxFoods; i++)
	{
		string name = "Food(" + i;
		name += ")";
		//objs.push_back(new GameObject("Food(" + i + ')'));�̷����ϰų�
		GameObject* newObject = new GameObject(name);
		newObject->addComponent<FoodScript>();

		objs.push_back(newObject);
	}
	GameObject* monster = new GameObject("monster");
	monster->addComponent<MonsterScript>();
	GameObject* ghost = new GameObject("ghost");
	ghost->addComponent<GhostScript>();

	objs.push_back(new GameObject("monster"));
	objs.push_back(new GameObject("ghost"));

}

GameObject::~GameObject() {}


tamplate<typename T>
void GameObject::addComponent()
{
	if (getComponent<T>)() != nullptr)return;
	T* newComp = new T(this);
	if (dynamic_cast<component *>(newComp) == nullptr)
		(
			delete newComp;
	return;
	)
		components.push_back(newComp);
}









for (auto obj : GameObject::gameObjects)
{
	obj->traverseStart();
}

while (!Input::GetKeyDown(KeyCode::Esc)) {
	screen.clear();
	// update		
	for (auto obj : GameObject::gameObjects)
	{
		obj->traverseUpdate();
	}
	// erase in active objects

	// draw

	screen.render();
	Sleep(100);

	Input::EndOfFrame();
}
return;
}