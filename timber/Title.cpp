#include "Title.h"
#include "InputMgr.h"

Title::Title(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), titleOn(true), wordBlink(true), menuOn(true), timer(0.f),
	menuIndex(0),Exiter(false)
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
	
	sf::Vector2f menuSelectorSize(button1->GetSize().x + 4,
		button1->GetSize().y + 4);
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
	if (menuOn)
	{
		SpriteGo::Update(dt);
		timer += dt;
		if (Exiter)
		{
			icon->Update(dt);


		}
		else if (timer >= 1.f)
		{
			if (titleOn)
			{
				wordBlink = !wordBlink;
			}
			
			timer = 0.f;
		}

		else if (!titleOn)
		{
			wordBlink = false;
			if (menuIndex > 0 && InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				menuIndex--;
				menuSelector.setPosition
				(menuSelector.getPosition().x - (1920 * 0.25f), 
					menuSelector.getPosition().y);
				soundChop.play();
			}
			else if (menuIndex < 2 && InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				menuIndex++;
				menuSelector.setPosition
				(menuSelector.getPosition().x + (1920 * 0.25f),
					menuSelector.getPosition().y);
				soundChop.play();
			}

			if (InputMgr::GetKeyDown(sf::Keyboard::Return))
			{
				switch (menuIndex)
				{
				case 0:
					menuOn = false;
					break;

				case 1:
					menuOn = false;
					break;
				case 2:
					timer = 0.f;
					Exiter = true;
					icon->Fire(sf::Vector2f(-1000.f, -1000.f));
					soundDeath.play();
					break;
				}
				soundChop.play();
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Return) && titleOn)
		{
			titleOn = false;
			soundChop.play();
		}
		icon->SetSize(2.8 + (timer / 10), 2.8 + (timer / 10));


	}
	
}

void Title::Draw(sf::RenderWindow& window)
{
	if (menuOn)
	{
		SpriteGo::Draw(window);
		icon->Draw(window);
		if (wordBlink)
		{
			window.draw(pressEnt);
		}
		if (!titleOn)
		{
			window.draw(menuSelector);
			button1->Draw(window);
			button2->Draw(window);
			button3->Draw(window);
			
		}
		if (Exiter)
		{
			screenChop->Draw(window);
			if (timer >= 2.f)
			{
				window.close();
			}
		}
	}
	
}
