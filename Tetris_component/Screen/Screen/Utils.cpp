#include "Utils.h"

Vector2 Vector2::zero{ 0, 0 };
Vector2 Vector2::ones{ 1, 1 };
Vector2 Vector2::up{ 0, 1 };
Vector2 Vector2::down{ 0, -1 };
Vector2 Vector2::left{ -1, 0 };
Vector2 Vector2::right{ 1, 0 };


INPUT_RECORD Input::InputRecord[128];
DWORD Input::Events;

bool Input::evaluated = false;
bool Input::gotMouseEvent = false;
bool Input::gotKeyEvent = false;
Vector2 Input::mousePosition{ -1, -1 };
WORD Input::vKeyCode{ 0 };

Vector2 operator-(Vector2& a, const Vector2& b)
{
	return (a.operator-(b));
}

double ::Distance(Vector2& a, const Vector2& b)
{
	return (a.operator-(b)).magnitude();
}

//static vector<WORD> keyCodeTable{
//	VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
//	VK_ESCAPE, VK_RETURN, 
//	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
//	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
//};

static void GetEvent()
{
	evaluated = true;
	DWORD numEvents = 0;
	//double이라는 자료형 32비트?.
	GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numEvents);
	if (!numEvents) return;

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), InputRecord, numEvents, &Events);
	for (int i = 0; i < Events; i++) {
		if (InputRecord[i].EventType == MOUSE_EVENT) {
			if (InputRecord[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				COORD coord;
				coord.X = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
				coord.Y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				mousePosition.x = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
				mousePosition.y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
				gotMouseEvent = true;
			}
		}
		else if (InputRecord[i].EventType == KEY_EVENT) {
			if (InputRecord[i].Event.KeyEvent.bKeyDown) {
				vKeyCode = InputRecord[i].Event.KeyEvent.wVirtualKeyCode;
				gotKeyEvent = true;
			}
		}
	}
}
bool GetMouseEvent(Vector2& pos) {
	if (evaluated == false) GetEvent();

	if (gotMouseEvent == true) {
		pos = mousePosition;
		return true;
	}
	return false;
}

bool GetKeyEvent(WORD& keyCode) {
	if (evaluated == false) GetEvent();

	if (gotKeyEvent == true) {
		keyCode = vKeyCode;
		return true;
	}
	return false;
}




bool GetKeyDown(KeyCode key) {
	if (evaluated == false) GetEvent();

	if (gotKeyEvent == true) return keyCodeTable[(int)key] == vKeyCode;
	return false;
}


Screen* Screen::instance = nullptr;