#include "Title.h"
#include "InputMgr.h"
#include "GameManager.h"
Title::Title(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), titleOn(true), wordBlink(true), menuOn(true), timer(0.f),
	menuIndex(0), Exiter(false), weaponSelectOn(false),
	characterOn(false), twoPlayerOn(false), characterIndex(0), playerCard(4), p1Selected(false), p2Selected(false)
	,mode(1), checkCharSelect(0)
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

	texPlayer1.loadFromFile("graphics/player1.png");
	texPlayer2.loadFromFile("graphics/player2.png");
	texPlayer3.loadFromFile("graphics/player3.png");
	texPlayer4.loadFromFile("graphics/player4.png");

	player1 = new SpriteGo(texPlayer1);
	player2 = new SpriteGo(texPlayer2);
	player3 = new SpriteGo(texPlayer3);
	player4 = new SpriteGo(texPlayer4);

	player1->SetOrigin(Origins::MC);
	player2->SetOrigin(Origins::MC);
	player3->SetOrigin(Origins::MC);
	player4->SetOrigin(Origins::MC);

	player1->SetPosition(1920.f * 0.2f, 1080.f * 0.8f);
	player2->SetPosition(1920.f * 0.4f, 1080.f * 0.8f);
	player3->SetPosition(1920.f * 0.6f, 1080.f * 0.8f);
	player4->SetPosition(1920.f * 0.8f, 1080.f * 0.8f);

	//뒷배경

	texPlayerCard.loadFromFile("graphics/player_card.png");

	for (auto& PlayerCards : playerCard)
	{
		PlayerCards = new SpriteGo(texPlayerCard);
		PlayerCards->SetOrigin(Origins::MC);
	}
	playerCard[0]->SetPosition(player1->GetPosition());
	playerCard[1]->SetPosition(player2->GetPosition());
	playerCard[2]->SetPosition(player3->GetPosition());
	playerCard[3]->SetPosition(player4->GetPosition());

	sf::Vector2f characterSelectorSize(playerCard[0]->GetSize().x + 4, playerCard[0]->GetSize().y + 4);

	p1CharacterSelector.setSize(characterSelectorSize);
	Utils::SetOrigin(p1CharacterSelector, Origins::MC);
	p1CharacterSelector.setPosition(player1->GetPosition());
	p1CharacterSelector.setFillColor(sf::Color::Yellow);

	p2CharacterSelector.setSize(characterSelectorSize);
	Utils::SetOrigin(p2CharacterSelector, Origins::MC);
	p2CharacterSelector.setPosition(player1->GetPosition());
	p2CharacterSelector.setFillColor(sf::Color::Cyan);
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
	twoPlayerOn = false;
	p1Selected = false;
	p2Selected = false;
	p1CharacterSelector.setPosition(player1->GetPosition());
	p2CharacterSelector.setPosition(player1->GetPosition());
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
			if (menuIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Left) && checkCharSelect == 0) //왼쪽 방향키
			{
				menuIndex--;
				menuSelector.setPosition
				(menuSelector.getPosition().x - (1920 * 0.25f),
					menuSelector.getPosition().y);
				soundChop.play();
			}
			else if (menuIndex < 2 && InputMgr::GetKeyDown(sf::Keyboard::Right) && checkCharSelect == 0) //오른쪽 방향키
			{
				menuIndex++;
				menuSelector.setPosition
				(menuSelector.getPosition().x + (1920 * 0.25f),
					menuSelector.getPosition().y);
				soundChop.play();
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Return) && !characterOn) //메뉴 선택+입장
			{
				switch (menuIndex)
				{
				case 0: //1인 플레이
					checkCharSelect = 1;
					characterOn = true; //캐릭터 선택
					twoPlayerOn = false;
					mode = 1;
					break;

				case 1: //2인 플레이
					checkCharSelect = 2;
					characterOn = true; //캐릭터 선택
					twoPlayerOn = true;
					mode = 2;

					break;
				case 2: //게임 종료
					timer = 0.f;
					Exiter = true;
					icon->Fire(sf::Vector2f(-1000.f, -1000.f));
					soundDeath.play();
					break;
				}
				InputMgr::Clear();
				soundChop.play();
			}
			using namespace std;
			if (characterOn && !p1Selected) //1p 캐릭터 선택
			{
				if (characterIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Left)) //왼쪽 방향키
				{
					characterIndex--;
					p1CharacterSelector.setPosition
					(p1CharacterSelector.getPosition().x - (1920 * 0.2f),
						p1CharacterSelector.getPosition().y);
					soundChop.play();
				}
				else if (characterIndex < 3 && InputMgr::GetKeyDown(sf::Keyboard::Right)) //오른쪽 방향키
				{
					characterIndex++;
					p1CharacterSelector.setPosition
					(p1CharacterSelector.getPosition().x + (1920 * 0.2f),
						p1CharacterSelector.getPosition().y);
					soundChop.play();
				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Return))
				{
					checkCharSelect--;
					switch (characterIndex)
					{
					case 0:
						player1File = "graphics/player1.png";
						if (!twoPlayerOn)
						{
							menuOn = false;
							characterOn = false;
						}
						break;

					case 1:
						player1File = "graphics/player2.png";
						if (!twoPlayerOn)
						{
							menuOn = false;
							characterOn = false;
						}
						break;

					case 2:
						player1File = "graphics/player3.png";
						if (!twoPlayerOn)
						{
							menuOn = false;
							characterOn = false;
						}
						break;
					case 3:
						player1File = "graphics/player4.png";
						if (!twoPlayerOn)
						{
							menuOn = false;
							characterOn = false;
						}
						break;
					}
					characterIndex = 0;
					InputMgr::Clear();
					p1Selected = true;
				}	
			}
			if (twoPlayerOn && p1Selected) //2p 캐릭터 선택
			{
				if (characterIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Left)) //왼쪽 방향키
				{
					characterIndex--;
					p2CharacterSelector.setPosition
					(p2CharacterSelector.getPosition().x - (1920 * 0.2f),
						p2CharacterSelector.getPosition().y);
					soundChop.play();
				}
				else if (characterIndex < 3 && InputMgr::GetKeyDown(sf::Keyboard::Right)) //오른쪽 방향키
				{
					characterIndex++;
					p2CharacterSelector.setPosition
					(p2CharacterSelector.getPosition().x + (1920 * 0.2f),
						p2CharacterSelector.getPosition().y);
					soundChop.play();
				}
				if (InputMgr::GetKeyDown(sf::Keyboard::Return))
				{
					checkCharSelect--;
					p1Selected = false;
					switch (characterIndex)
					{
					case 0:
						player2File = "graphics/player1.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
						break;

					case 1:
						player2File = "graphics/player2.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
						break;

					case 2:
						player2File = "graphics/player3.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
						break;
					case 3:
						player2File = "graphics/player4.png";
						menuOn = false;
						twoPlayerOn = false;
						characterOn = false;
						break;
					}
					characterIndex = 0;
					p2Selected = true;
					InputMgr::Clear();
				}
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
			window.draw(p1CharacterSelector);
			if (characterOn && p1Selected)
			{
				window.draw(p2CharacterSelector);
			}
			for (int i = 0; i < 4; i++)
			{
				playerCard[i]->Draw(window);
			}
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

bool Title::isCharacterSelect(int pNum)
{
	if (pNum == 1)
	{
		return p1Selected;
	}
	if (pNum == 2)
	{
		return p2Selected;
	}
	
}

int Title::GetMod() const
{
	return mode;
}
