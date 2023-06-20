#include "GameManager.h"

GameManager::GameManager()
	:isPause(true), score(0), screenWidth(1920), screenHeight(1080),
	uiTimerWidth(400.f), uiTimerHeight(80.f), duration(5.f), timer(duration),
	window(sf::VideoMode(screenWidth, screenHeight), "Timber!", sf::Style::Default)
{
	 font.loadFromFile("fonts/KOMIKAP_.ttf");

	 textMessage.setFont(font);
	 textMessage.setString("PRESS ENTER TO START!");
	 textMessage.setCharacterSize(75);
	 textMessage.setFillColor(sf::Color::White);
	 Utils::SetOrigin(textMessage, Origins::MC);
	 textMessage.setPosition(screenWidth * 0.5f, screenHeight * 0.5f);

	 textScore.setFont(font);
	 textScore.setString("SCORE: ???");
	 textScore.setCharacterSize(100);
	 textScore.setFillColor(sf::Color::White);
	 Utils::SetOrigin(textScore, Origins::TL);
	 textScore.setPosition(20.f, 20.f);

	 uiTimer.setSize(sf::Vector2f(uiTimerWidth, uiTimerHeight));
	 Utils::SetOrigin(uiTimer, Origins::BC);
	 uiTimer.setPosition(screenWidth * 0.5f, screenHeight - 50.f);
	 uiTimer.setFillColor(sf::Color::Red);

	 texBackground.loadFromFile("graphics/background.png");
	 texTree.loadFromFile("graphics/tree.png");
	 texCloud.loadFromFile("graphics/cloud.png");
	 texBee.loadFromFile("graphics/bee.png");
	 texBranch.loadFromFile("graphics/branch.png");
	 texPlayer.loadFromFile("graphics/player.png");

	 gameObjects.push_back(new SpriteGo(texBackground, sf::Vector2f(1.f, 0.f), "BG", { 0, 0 }));

	 for (int i = 0; i < 3; ++i)
	 {
		 MovingBgObj* newGo = new MovingBgObj(texCloud, sf::Vector2f(-1.f, -1.f), "Cloud");
		 newGo->SetSpeedRange(sf::Vector2f(300.f, 600.f));
		 newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
			 sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
		 newGo->SetPosXRange(0, 0);
		 newGo->SetPosYRange(-400, -100);
		 gameObjects.push_back(newGo);
	 }

	 tree = new Tree(texTree, sf::Vector2f(1.f, 0.f), "Tree");
	 tree->SetOrigin(Origins::TC);
	 tree->SetPosition(screenWidth * 0.5f, 0.f);
	 gameObjects.push_back(tree);

	 player = new Player(texPlayer, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
	 player->SetTree(tree);
	 gameObjects.push_back(player);

	 newGo = new MovingBgObj(texBee, sf::Vector2f(-1.f, -1.f), "Bee");
	 newGo->SetSpeedRange(sf::Vector2f(100.f, 200.f));
	 newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
		 sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
	 newGo->SetPosXRange(0, 0);
	 newGo->SetPosYRange(0, 300);
	 newGo->SetMoveY(2.f, 50.f);
	 gameObjects.push_back(newGo);

	 texTitle.loadFromFile("graphics/title.png");
	 title = new Title(texTitle, sf::Vector2f(1.f, 0.f), "TT", { 0, 0 });
	 gameObjects.push_back(title);

	 for (auto obj : gameObjects)
	 {
		 obj->Init();
		 tree->InitBranches();
	 }
	 
}

void GameManager::Play()
{
    while (window.isOpen())
    {
        WindowHandler();
        
        Update();
        window.clear();

        Draw();
        window.display();
    }
}

void GameManager::Update()
{
    //메뉴일경우
    if (title->IsMenu())
    {
        title->Update(dt);
    }

    //일시정지 아닐때
    else if (!isPause)
    {
        timer -= dt;

        //시간경과
        if (timer < 0.f)
        {
            textMessage.setString("OUT OF TIME");
            Utils::SetOrigin(textMessage, Origins::MC);
            isPause = true;
            player->Die(true);
        }
        //충돌후 죽음
        else if (!player->IsHeAlive())
        {
            textMessage.setString("Game Over");
            Utils::SetOrigin(textMessage, Origins::MC);
            isPause = true;
        }
        //게임진행중
        else
        {
            float normTime = timer / duration;
            float timeSizeX = uiTimerWidth * normTime;
            uiTimer.setSize(sf::Vector2f(timeSizeX, uiTimerHeight));

            for (auto obj : gameObjects)
            {
                if (obj->GetActive())
                    obj->Update(dt);
            }

            if (InputMgr::GetKeyDown(sf::Keyboard::Right) &&
                !InputMgr::GetKey(sf::Keyboard::Left) ||
                InputMgr::GetKeyDown(sf::Keyboard::Left) &&
                !InputMgr::GetKey(sf::Keyboard::Right))
            {
                if (timer <= duration - 0.1f)
                {
                    score += 1;
                    timer += 0.15f;
                }
            }

            std::stringstream ss;
            ss << "SCORE: " << score;
            textScore.setString(ss.str());
        }
    }
    //일시정지일때
    else
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Return))
        {
            //죽음 직후의 일시정지일때
            if (!player->IsHeAlive())
            {
                timer = duration;
                    score = 0;
                    for (auto obj : gameObjects)
                    {
                        obj->Init();
                    }
                title->MenuChange(true);
                    textMessage.setString("PRESS ENTER TO START!");
                Utils::SetOrigin(textMessage, Origins::MC);

            }
            //게임시작시의 일시정지일때
            else
            {
                isPause = false;
            }
        }
    }

}

void GameManager::Draw()
{
    for (auto obj : gameObjects)
    {
        if (obj->GetActive())
        {
            obj->Draw(window);
        }
    }
    //메뉴일떄
    if (title->IsMenu()) {}
    //게임중일때
    else
    {
        window.draw(textScore);
        window.draw(uiTimer);
        if (isPause)
        {
            window.draw(textMessage);
        }
    }
}

void GameManager::Release()
{
    for (auto obj : gameObjects)
    {
        obj->Release();
        delete obj;
    }
}

void GameManager::WindowHandler()
{
    InputMgr::Clear();
    deltaTime = clock.restart();
    dt = deltaTime.asSeconds();

    while (window.pollEvent(event))
    {
        InputMgr::Update(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}
