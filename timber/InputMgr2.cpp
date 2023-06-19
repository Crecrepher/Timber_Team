#include "InputMgr2.h"
#include <iostream>
#include <algorithm>

vector<bool> InputMgr2::downList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::upList(Keyboard::Key::KeyCount);


void InputMgr2::ClearInput()
{
	for (int i = 0; i < Keyboard::Key::KeyCount; i++)
	{
		downList[i] = false;
		upList[i] = false;
	}
}

//백터는 크기를 늘리거나 줄이는데엔 코드가 많이들어가지만
//검색 및 접근이 편하다
//더블클릭처럼 커스텀하기엔 list가 더 낫다
void InputMgr2::UpdateInput(sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (!ingList[ev.key.code])
		{
			downList[ev.key.code] = true;
			ingList[ev.key.code] = true;
		}
		break;
	case sf::Event::KeyReleased:
		ingList[ev.key.code] = false;
		upList[ev.key.code] = true;
		break;
	}
}

bool InputMgr2::GetKeyDown(sf::Keyboard::Key key)
{
	return downList[key];
}

bool InputMgr2::GetKey(sf::Keyboard::Key key)
{
	return ingList[key];
}

bool InputMgr2::GetKeyUp(sf::Keyboard::Key key)
{
	return upList[key];
}

