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
	//loop돌아가기 저에 다초기화 시켜줄때 추가하기.
	GameObject map("Map");//map공간 만들기.다음으로 grid공간에 대한 정보들 넣어줘야함
	auto& objs = GameObject::gameObjects;
	//& objs 안쓰면 벡터 객체가 있는데 그거를 또 복사해서 사용하는 것.
	const int maxFoods = 10;

	map.addComponent<GridScript>();
	GridScript* comp = map.getComponent<GridScript>();



	GridScript grid(&map, 40, 40);
	//map.components.push_back(&grid);
	//이게 게임엔진이니까 friends관계 떄문에 뜨는 것이다.안에 접근할 수 있는 방법중 하나. 유니티에서는 addComponents,getComponents과 같은 것이다.
	//어느 클래스에 있는 함수인가?게임오브젝트한테 요청해야하는 사항들. = 주체
	//addComp 구현함
	map.addComponent<GridScript>();
	GridScript* comp = map.getComponent<GridScript>();

	for (int i = 0; i < maxFoods; i++)
	{
		string name = "Food(" + i;
		name += ")";
		//objs.push_back(new GameObject("Food(" + i + ')'));이렇게하거나
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