#include "Title.h"
#include "InputMgr.h"

Title::Title(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), titleOn(true), wordBlink(true), menuOn(true), timer(0.f), menuIndex(0),Exiter(false),
	characterOn(false), twoPlayerOn(false), characterIndex(0)
{
	texicon.loadFromFile("graphics/timber_icon.png");
	icon = new EffectGo(texicon);
	icon->Init();
	icon->SetOrigin(Origins::MC);
	icon->SetPosition(1920 / 2.f, 1080.f / 3.f);


	texbutton1.loadFromFile("graphics/b1.png");
	texbutton2.loadFromFile("graphics/b2.png");
	texbutton3.loadFromFile("graphics/b3.png");
	texscreenChop.loadFromFile("graphics/chop_screen.png");

	button1 = new SpriteGo(texbutton1);
	button2 = new SpriteGo(texbutton2);
	button3 = new SpriteGo(texbutton3);
	screenChop = new SpriteGo(texscreenChop);

	button1->SetOrigin(Origins::MC);
	button2->SetOrigin(Origins::MC);
	button3->SetOrigin(Origins::MC);
	screenChop->SetOrigin(Origins::TC);

	button1->SetPosition(1920 * 0.25f, 1080.f * 0.8f);
	button2->SetPosition(1920 * 0.5f, 1080.f * 0.8f);
	button3->SetPosition(1920 * 0.75f, 1080.f * 0.8f);
	screenChop->SetPosition(1920 * 0.5f,0);
	
	//메뉴 선택하는 초록 네모
	sf::Vector2f menuSelectorSize(button1->GetSize().x + 4, button1->GetSize().y + 4);
	menuSelector.setSize(menuSelectorSize);
	Utils::SetOrigin(menuSelector,Origins::MC);
	menuSelector.setPosition(button1->GetPosition());
	menuSelector.setFillColor(sf::Color::Green);

	font.loadFromFile("fonts/KOMIKAP_.ttf");
	pressEnt.setFont(font);

	pressEnt.setString("PRESS ENTER");
	pressEnt.setCharacterSize(125);
	pressEnt.setFillColor(sf::Color::White);
	Utils::SetOrigin(pressEnt, Origins::MC);
	pressEnt.setPosition(1920.f * 0.5f, 1080.f * 0.7f);

	soundBufferChop.loadFromFile("sound/chop.wav");
	soundBufferDeath.loadFromFile("sound/death.wav");

	soundChop.setBuffer(soundBufferChop);
	soundDeath.setBuffer(soundBufferDeath);

	//----yl start----
	//캐릭터 선택 4개
	/*texPlayer[0]->loadFromFile("graphics/player1.png");
	texPlayer[1]->loadFromFile("graphics/player2.png");
	texPlayer[2]->loadFromFile("graphics/player3.png");
	texPlayer[3]->loadFromFile("graphics/player4.png");*/

	texPlayer1.loadFromFile("graphics/player1.png");
	texPlayer2.loadFromFile("graphics/player2.png");
	texPlayer3.loadFromFile("graphics/player3.png");
	texPlayer4.loadFromFile("graphics/player4.png");

	/*for (int i = 0; i < 4; i++)
	{
		player[i] = new SpriteGo(*texPlayer[i]);
		player[i]->SetOrigin(Origins::MC);
		player[i]->SetPosition(1920.f * (0.2f) * (i + 1), 1080.f * 0.7f);
	}*/

	player1 = new SpriteGo(texPlayer1);
	player2 = new SpriteGo(texPlayer2);
	player3 = new SpriteGo(texPlayer3);
	player4 = new SpriteGo(texPlayer4);

	player1->SetOrigin(Origins::MC);
	player2->SetOrigin(Origins::MC);
	player3->SetOrigin(Origins::MC);
	player4->SetOrigin(Origins::MC);

	player1->SetPosition(1920.f * 0.2f, 1080.f * 0.7f);
	player2->SetPosition(1920.f * 0.4f, 1080.f * 0.7f);
	player3->SetPosition(1920.f * 0.6f, 1080.f * 0.7f);
	player4->SetPosition(1920.f * 0.8f, 1080.f * 0.7f);

	//뒷배경

	texPlayerCard.loadFromFile("graphics/player4.png");
	playerCard = new SpriteGo(texPlayerCard);
	//작성중
	/*int i = 0;
	for (auto& PlayerCards : playerCard)
	{
		PlayerCards = new SpriteGo(texPlayerCard);
		PlayerCards->SetOrigin(Origins::MC);
		sf::Vector2f posPCard = player[i]->GetPosition();
		PlayerCards->SetPosition(posPCard);
		i++;
	}*/

	//플레이어 선택 네모
	/*sf::Vector2f characterSelectorSize(playerCard[0]->GetSize().x + 4, playerCard[0]->GetSize().y + 4);
	characterSelector.setSize(characterSelectorSize);
	Utils::SetOrigin(characterSelector, Origins::MC);
	characterSelector.setPosition(playerCard[0]->GetPosition());
	characterSelector.setFillColor(sf::Color::Yellow);*/

	sf::Vector2f characterSelectorSize(playerCard->GetSize().x + 4, playerCard->GetSize().y + 4);
	characterSelector.setSize(characterSelectorSize);
	Utils::SetOrigin(characterSelector, Origins::MC);
	characterSelector.setPosition(playerCard->GetPosition());
	characterSelector.setFillColor(sf::Color::Yellow);

	//----yl end----


}

Title::~Title()
{
}

bool Title::IsMenu() const
{
	return menuOn;
}

void Title::MenuChange(bool in)
{
	menuOn = in;
}

void Title::Init()
{
	SpriteGo::Init();
}

void Title::Release()
{
	SpriteGo::Release();

}

void Title::Update(float dt)
{
	if (menuOn) //메뉴 화면
	{
		SpriteGo::Update(dt);
		timer += dt;
		if (Exiter)
		{
			icon->Update(dt);
		}
		else if (timer >= 1.f)
		{
			if (titleOn) //타이틀 화면
			{
				wordBlink = !wordBlink; //press enter 깜빡이기
			}

			timer = 0.f;
		}

		else if (!titleOn) //타이틀 종료->메뉴 화면
		{
			wordBlink = false; //press enter 화면에서 삭제
			if (menuIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Left)) //왼쪽 방향키
			{
				menuIndex--;
				menuSelector.setPosition
				(menuSelector.getPosition().x - (1920 * 0.25f),
					menuSelector.getPosition().y);
				soundChop.play();
			}
			else if (menuIndex < 2 && InputMgr::GetKeyDown(sf::Keyboard::Right)) //오른쪽 방향키
			{
				menuIndex++;
				menuSelector.setPosition
				(menuSelector.getPosition().x + (1920 * 0.25f),
					menuSelector.getPosition().y);
				soundChop.play();
			}
			if (InputMgr::GetKeyDown(sf::Keyboard::Return)) //메뉴 선택+입장
			{
				switch (menuIndex)
				{
				case 0: //1인 플레이
					//menuOn = false;
					characterOn = true; //캐릭터 선택
					break;

				case 1: //2인 플레이
					//menuOn = false;
					characterOn = true; //캐릭터 선택
					twoPlayerOn = true;
					break;
				case 2: //게임 종료
					timer = 0.f;
					Exiter = true;
					icon->Fire(sf::Vector2f(-1000.f, -1000.f));
					soundDeath.play();
					break;
				}
				soundChop.play();
			}
			//yl start
			if (characterOn == true)
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Num1)) //왼쪽 방향키
				{
					player1File = "graphics/player1.png";
					std::cout << "player1File is in getkeydown " << player1File << std::endl;
					if (!twoPlayerOn)
					{
						menuOn = false;
						characterOn = false;
					}
				}
				else if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
				{
					player1File = "graphics/player2.png";
					if (!twoPlayerOn)
					{
						menuOn = false;
						characterOn = false;
					}
				}
				else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
				{
					player1File = "graphics/player3.png";
					if (!twoPlayerOn)
					{
						menuOn = false;
						characterOn = false;
					}
				}
				else if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
				{
					player1File = "graphics/player4.png";
					if (!twoPlayerOn)
					{
						menuOn = false;
						characterOn = false;
					}
				}
				if (twoPlayerOn == true)
				{
					if (characterIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Num1)) //num1키
					{
						player2File = "graphics/player1.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
					}
					else if (characterIndex < 1 && InputMgr::GetKeyDown(sf::Keyboard::Num2)) //num2키
					{
						player2File = "graphics/player2.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
					}
					else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
					{
						player2File = "graphics/player3.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
					}
					else if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
					{
						player2File = "graphics/player4.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
					}
				}
				//yl end
			}
			
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Return) && titleOn) //title에서 메뉴로 이동
		{
			titleOn = false; //title 종료
			soundChop.play();
		}
		icon->SetSize(2.8 + (timer / 10), 2.8 + (timer / 10));
	}
}

void Title::Draw(sf::RenderWindow& window)
{
	if (menuOn) //메뉴 화면
	{
		SpriteGo::Draw(window);
		icon->Draw(window);
		if (wordBlink)
		{
			window.draw(pressEnt);
		}
		if (!titleOn && !characterOn) //title이 꺼지면 메뉴 그리기
		{
			window.draw(menuSelector);
			button1->Draw(window);
			button2->Draw(window);
			button3->Draw(window);
		}
		if (characterOn)
		{
			window.draw(characterSelector);
			/*for (int i = 0; i < 4; i++)
			{
				player[i]->Draw(window);
			}*/
			player1->Draw(window);
			player2->Draw(window);
			player3->Draw(window);
			player4->Draw(window);
		}
		if (Exiter) //게임 종료
		{
			screenChop->Draw(window);
			if (timer >= 2.f)
			{
				window.close();
			}
		}
	}
}

std::string Title::GetplayerFile(int pNum)
{
	if (pNum == 1)
	{
		return player1File;
	}
	else if (pNum == 2)
	{
		return player2File;
	}
	else
	{
		return NULL;
	}
}
