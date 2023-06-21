#include "GameManager.h"
GameManager::GameManager()
	:isPause(true), screenWidth(1920), screenHeight(1080),
	uiTimerWidth(400.f), uiTimerHeight(80.f), duration(5.f), timer(duration),
	window(sf::VideoMode(screenWidth, screenHeight), "Timber!", sf::Style::Default),
    Gamemode(1), scoreLeft(0), scoreRight(0), playerOneLife(true), playerTwoLife(true),doInit(true), p1changed(false)
	,titleMusicPlaying(false), playMusicPlaying(false)
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
	 texPlayer.loadFromFile("graphics/player1.png");
	 texPlayerSecond.loadFromFile("graphics/player1.png");

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

	 treeSecond = new Tree(texTree, sf::Vector2f(1.f, 0.f), "Tree2");
	 treeSecond->SetOrigin(Origins::TC);
	 treeSecond->SetPosition(screenWidth * 0.75f, 0.f);
	 treeSecond->SetSize(0.7f, 1.f);
	 treeSecond->SetBranchSize(0.7f, 0.7f);
	 treeSecond->SetChopSize(0.7f, 1.f);

	 player = new Player(texPlayer, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
	 player->SetTree(tree);

	 playerSecond = new Player(texPlayerSecond, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
	 playerSecond->SetTree(treeSecond);
	 playerSecond->SetSize(0.7f, 0.7f);

	 newGo = new MovingBgObj(texBee, sf::Vector2f(-1.f, -1.f), "Bee");
	 newGo->SetSpeedRange(sf::Vector2f(100.f, 200.f));
	 newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
		 sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
	 newGo->SetPosXRange(0, 0);
	 newGo->SetPosYRange(0, 300);
	 newGo->SetMoveY(2.f, 50.f);
	 gameObjects.push_back(newGo);

	 //yl start
	 SoundBufferPlay.loadFromFile("sound/bgm_play.wav");
	 SoundBufferTitle.loadFromFile("sound/bgm_main.wav");

	 soundPlay.setBuffer(SoundBufferPlay);
	 soundTitle.setBuffer(SoundBufferTitle);

	 soundTitle.setLoop(true);
	 soundPlay.setLoop(true);
	 //yl end

	 texTitle.loadFromFile("graphics/title.png");
	 title = new Title(texTitle, sf::Vector2f(1.f, 0.f), "TT", { 0, 0 });
	 title->Init();
	 gameObjects.push_back(title);

	 gameObjects.push_back(tree);
	 gameObjects.push_back(treeSecond);
	 gameObjects.push_back(player);
	 gameObjects.push_back(playerSecond);

	 
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
	if (title->IsMenu())
	{
		if (!titleMusicPlaying)
		{
			soundTitle.play();
			titleMusicPlaying = true;
		}
		title->Update(dt);
		Gamemode = title->GetMod();

		if (title->isCharacterSelect(1) && !(title->isCharacterSelect(2)) && !p1changed)
		{
			std::string fileRoute = title->GetplayerFile(1);
			texPlayer.loadFromFile(fileRoute);
			player->SetTexture(texPlayer);
			p1changed = true;
		}
		if (title->isCharacterSelect(2))
		{
			std::string fileRoute = title->GetplayerFile(2);
			texPlayerSecond.loadFromFile(fileRoute);
			playerSecond->SetTexture(texPlayerSecond);
		}
	}
	else if (Gamemode == 1)
	{
		if (doInit)
		{
			doInit = false;
			Init();
		}
		// 2. Update
		if (!isPause)
		{
			if (titleMusicPlaying)
			{
				soundTitle.stop();
				titleMusicPlaying = false;
			}
			if (!playMusicPlaying)
			{
				soundPlay.play();
				playMusicPlaying = true;
			}
			p1changed = false;
			timer -= dt;

			if (timer < 0.f)
			{
				textMessage.setString("OUT OF TIME");
				Utils::SetOrigin(textMessage, Origins::MC);
				isPause = true;
				player->Die(true);
				playerOneLife = false;
				soundPlay.stop();
				playMusicPlaying = false;
			}
			else if (!playerOneLife)
			{
				textMessage.setString("Game Over");
				Utils::SetOrigin(textMessage, Origins::MC);
				isPause = true;
				soundPlay.stop();
				playMusicPlaying = false;
			}
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
						scoreLeft += 1;
						timer += 0.15f;
					}

				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Right))
				{
					tree->GetKeyDownRight();
					player->KeyDownButtonRight();
					if (player->CheckCollide())
					{
						player->Die(false);
						playerOneLife = false;
					}
				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Left))
				{
					tree->GetKeyDownLeft();
					player->KeyDownButtonLeft();
					if (player->CheckCollide())
					{
						player->Die(false);
						playerOneLife = false;
					}
				}
				if (InputMgr::GetKeyUp(sf::Keyboard::Right))
					player->KeyUpButtonRight();
				if (InputMgr::GetKeyUp(sf::Keyboard::Left))
					player->KeyUpButtonLeft();


				std::stringstream ss;
				ss << "SCORE: " << scoreLeft;
				textScore.setString(ss.str());
			}
		}
		else
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Return))
			{
				if (!player->IsHeAlive())
				{
					playerOneLife = true;
					timer = duration;
					scoreLeft = 0;
					title->MenuChange(true);
					textMessage.setString("PRESS ENTER TO START!");
					Utils::SetOrigin(textMessage, Origins::MC);
					for (auto obj : gameObjects)
					{
						obj->Init();
					}
					doInit = true;
				}
				else
				{
					isPause = false;
				}
				
			}
		}
	}
	else if (Gamemode == 2)
	{
		if (doInit)
		{
			doInit = false;
			Init();
		}
		if (!isPause)
		{
			if (titleMusicPlaying)
			{
				soundTitle.stop();
				titleMusicPlaying = false;
			}
			if (!playMusicPlaying)
			{
				soundPlay.play();
				playMusicPlaying = true;
			}
			if (playerOneLife)
				timer -= dt;
			if (playerTwoLife)
				timerSecond -= dt;

			if (playerOneLife == false && playerTwoLife == false)
			{
				isPause = true;
				soundPlay.stop();
				playMusicPlaying = false;
			}

			if (timer < 0.f && player->IsHeAlive())
			{
				playerOneLife = false;
				player->Die(true);
				
			}
			if (timerSecond < 0.f && playerSecond->IsHeAlive())
			{
				playerTwoLife = false;
				playerSecond->Die(true);
			}
			if (isPause)
			{
				if (scoreLeft > scoreRight)
					textMessage.setString("Player 1 Win");
				if (scoreLeft < scoreRight)
					textMessage.setString("Player 2 Win");
				else if (scoreLeft == scoreRight)
					textMessage.setString("Draw");

				Utils::SetOrigin(textMessage, Origins::MC);
			}
			else
			{
				float normTime = timer / duration;
				float normTimeSecond = timerSecond / duration;
				float timeSizeX = uiTimerWidth * normTime;
				float timeSizeXSec = uiTimerWidth * normTimeSecond;
				uiTimer.setSize(sf::Vector2f(timeSizeX, uiTimerHeight));
				uiTimerSecond.setSize(sf::Vector2f(timeSizeXSec, uiTimerHeight));

				for (auto obj : gameObjects)
				{
					if (obj->GetActive())
						obj->Update(dt);
				}

				//Player1 버튼 입력
				if (InputMgr::GetKeyDown(sf::Keyboard::D) && playerOneLife)
				{
					tree->GetKeyDownRight();
					player->KeyDownButtonRight();
					if (player->CheckCollide())
					{
						player->Die(false);
						playerOneLife = false;
					}

				}
				if (InputMgr::GetKeyDown(sf::Keyboard::A) && playerOneLife)
				{
					tree->GetKeyDownLeft();
					player->KeyDownButtonLeft();
					if (player->CheckCollide())
					{
						player->Die(false);
						playerOneLife = false;
					}
				}
				if (InputMgr::GetKeyUp(sf::Keyboard::D) && playerOneLife)
					player->KeyUpButtonRight();
				if (InputMgr::GetKeyUp(sf::Keyboard::A) && playerOneLife)
					player->KeyUpButtonLeft();



				//Player2 버튼 입력
				if (InputMgr::GetKeyDown(sf::Keyboard::Right) && playerTwoLife)
				{
					treeSecond->GetKeyDownRight();
					playerSecond->KeyDownButtonRight();
					if (playerSecond->CheckCollide())
					{
						playerSecond->Die(false);
						playerTwoLife = false;
					}

				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Left) && playerTwoLife)
				{
					treeSecond->GetKeyDownLeft();
					playerSecond->KeyDownButtonLeft();
					if (playerSecond->CheckCollide())
					{
						playerSecond->Die(false);
						playerTwoLife = false;
					}

				}
				if (InputMgr::GetKeyUp(sf::Keyboard::Right) && playerTwoLife)
					playerSecond->KeyUpButtonRight();
				if (InputMgr::GetKeyUp(sf::Keyboard::Left) && playerTwoLife)
					playerSecond->KeyUpButtonLeft();



				if (InputMgr::GetKeyDown(sf::Keyboard::D) && !InputMgr::GetKey(sf::Keyboard::A) ||
					InputMgr::GetKeyDown(sf::Keyboard::A) && !InputMgr::GetKey(sf::Keyboard::D))
				{
					if (playerOneLife)
					{
						timer += 1.15f;
						scoreLeft += 1;
					}
					if (timer >= duration)
						timer = duration;

				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Right) && !InputMgr::GetKey(sf::Keyboard::Left) ||
					InputMgr::GetKeyDown(sf::Keyboard::Left) && !InputMgr::GetKey(sf::Keyboard::Right))
				{
					if (playerTwoLife)
					{
						timerSecond += 1.15f;
						scoreRight += 1;
					}
					if (timerSecond >= duration)
						timerSecond = duration;
				}

				std::stringstream ssLeft;
				ssLeft << "SCORE: " << scoreLeft;
				textScore.setString(ssLeft.str());

				std::stringstream ssRight;
				ssRight << "SCORE: " << scoreRight;
				textScoreSecond.setString(ssRight.str());
			}
		}
		else
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Return))
			{
				if (!player->IsHeAlive())
				{
					playerOneLife = true;
					playerTwoLife = true;
					timer = duration;
					timerSecond = duration;
					scoreLeft = 0;
					scoreRight = 0;
					for (auto obj : gameObjects)
					{
						obj->Init();
					}
					title->MenuChange(true);
					textMessage.setString("PRESS ENTER TO START!");
					Utils::SetOrigin(textMessage, Origins::MC);
					doInit = true;
				}
				else
				{
					isPause = false;
				}
				
			}
		}
	}
}

void GameManager::Draw()
{	
	if (title->IsMenu()) 
	{
		title->Draw(window);
	}
	else if (Gamemode == 1)
	{
		for (auto obj : gameObjects)
		{
			if (obj->GetActive())
			{
				obj->Draw(window);
			}
		}

		window.draw(textScore);
		window.draw(uiTimer);

		if (isPause)
		{
			window.draw(textMessage);
		}
	}
	else if (Gamemode == 2)
	{
		for (auto obj : gameObjects)
		{
			if (obj->GetActive())
			{
				obj->Draw(window);
			}
		}

		window.draw(textScore);
		window.draw(textScoreSecond);
		window.draw(uiTimer);
		window.draw(uiTimerSecond);

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
		if (obj != nullptr)
		{
			obj->Release();
		}
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

void GameManager::Init()
{
    if (Gamemode == 1)
    {
		tree->SetOrigin(Origins::TC);
		tree->SetPosition(screenWidth * 0.5f, 0.f);
		tree->SetSize(1.f, 1.f);
		tree->SetBranchSize(1.f, 1.f);
		tree->SetChopSize(1.f, 1.f);
		player->SetSize(1.f, 1.f);

		treeSecond->SetSize(0.f, 0.f);
		treeSecond->SetBranchSize(0.f, 0.f);

		playerSecond->SetSize(0.f, 0.f);

		uiTimer.setPosition(screenWidth * 0.5f, screenHeight - 50.f);
		for (auto obj : gameObjects)
		{
			obj->Init();
		}
		tree->InitBranches();
    }
    //2인모드 설정
    //두번째 플레이어 나무, 캐릭터 추가, push back
    else if (Gamemode == 2)
    {
		//yl start
		p1changed = false;
		//yl end
        //1번 나무 위치, 크기 조절
        tree->SetPosition(screenWidth * 0.25f, 0.f);
        tree->SetSize(0.7f, 1.f);
        tree->SetBranchSize(0.7f, 0.7f);
        tree->SetChopSize(0.7f, 1.f);

        //1번 플레이어
        player->SetSize(0.7f, 0.7f);

        //2번 나무
		treeSecond->SetPosition(screenWidth * 0.75f, 0.f);
		treeSecond->SetSize(0.7f, 1.f);
		treeSecond->SetBranchSize(0.7f, 0.7f);
		treeSecond->SetChopSize(0.7f, 1.f);


        //2번 플레이어
        
        playerSecond->SetTree(treeSecond);
        playerSecond->SetSize(0.7f, 0.7f);


        //1번 타이머
        uiTimer.setPosition(screenWidth * 0.25f, screenHeight - 50.f);

        //2번 타이머
        uiTimerSecond.setSize(sf::Vector2f(uiTimerWidth, uiTimerHeight));
        Utils::SetOrigin(uiTimerSecond, Origins::BC);
        uiTimerSecond.setPosition(screenWidth * 0.75f, screenHeight - 50.f);
        uiTimerSecond.setFillColor(sf::Color::Red);

        textScoreSecond.setFont(font);
        textScoreSecond.setString("SCORE: ???");
        textScoreSecond.setCharacterSize(100);
        textScoreSecond.setFillColor(sf::Color::White);
        Utils::SetOrigin(textScoreSecond, Origins::TL);
        textScoreSecond.setPosition(1920.f * 0.5f, 20.f);

        for (auto obj : gameObjects)
        {
            obj->Init();
        }
        tree->InitBranches();
        treeSecond->InitBranches();
    }
}
