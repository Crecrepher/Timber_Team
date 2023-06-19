#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

// 스태틱 함수를 이용해서 키보드 및 마우스 입력을 검사할 수 있는 클래스

class InputMgr2
{
private:
	static vector<bool> downList; // 
	static vector<bool> ingList;  // 
	static vector<bool> upList;// 

public:
	static void ClearInput();
	static void UpdateInput(Event& ev);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);
};