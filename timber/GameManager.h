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
    bool isPause;

    bool playerOneLife;
    bool playerTwoLife;
    bool doInit;

    int scoreLeft;
    int scoreRight;

    int screenWidth;
    int screenHeight;

    float uiTimerWidth;
    float uiTimerHeight;

    int Gamemode;

    float duration;
    float timer;
    float timerSecond = duration;
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

    Tree* treeSecond;
    Player* playerSecond;
    sf::RectangleShape uiTimerSecond;
    sf::Text textScoreSecond;

    bool p1changed;
    sf::Texture texPlayerSecond;

    //yl start
    sf::Sound soundTitle;
    sf::Sound soundPlay;

    sf::SoundBuffer SoundBufferTitle;
    sf::SoundBuffer SoundBufferPlay;

    bool titleMusicPlaying;
    bool playMusicPlaying;
    //yl end


public:
    GameManager();

    void Init();

    void Play();
    void Update();
    void Draw();
    void Release();

    void WindowHandler();
};

