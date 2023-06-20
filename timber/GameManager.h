#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>

#include "Utils.h"
#include "MovingBgObj.h"
#include "InputMgr.h"
#include "Tree.h"
#include "Player.h"
#include "Title.h"


class GameManager
{
private:
    bool isPause = true;
    int score = 0;

    int screenWidth;
    int screenHeight;

    float uiTimerWidth;
    float uiTimerHeight;

    float duration;
    float timer;
    float dt;

    sf::RenderWindow window;
    sf::Event event;

    sf::Clock clock;
    sf::Time deltaTime;

    sf::Font font;

    sf::RectangleShape uiTimer;

    sf::Text textMessage;
    sf::Text textScore;

    sf::Texture texBackground;
    sf::Texture texTree;
    sf::Texture texCloud;
    sf::Texture texBee;
    sf::Texture texBranch;
    sf::Texture texPlayer;
    sf::Texture texTitle;

    std::vector<GameObject*> gameObjects;
    Tree* tree;
    Player* player;
    MovingBgObj* newGo;//¿Ã∏ßæ»πŸ≤€ π˙¿”
    Title* title;

public:
    GameManager();

    void Play();
    void Update();
    void Draw();
    void Release();

    void WindowHandler();
};

