#include "Title.h"

Title::Title(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), titleOn(true), wordBlink(true)
{
	texicon.loadFromFile("graphics/timber_icon.png");
	icon = new SpriteGo(texicon);
	icon->SetOrigin(Origins::MC);

	
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	pressEnt.setFont(font);
	pressEnt.setString("PRESS ENTER");
	pressEnt.setCharacterSize(125);
	pressEnt.setFillColor(sf::Color::White);
	Utils::SetOrigin(pressEnt, Origins::MC);
	pressEnt.setPosition(1920.f * 0.5f, 1080.f * 0.7f);

}

Title::~Title()
{
}

bool Title::IsTitle() const
{
	return titleOn;
}

void Title::TitleChange(bool in)
{
	titleOn = in;
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
	SpriteGo::Update(dt);
	timer += dt;
	if (timer >= 1.f)
	{
		wordBlink = !wordBlink;
		timer = 0.f;
	}
	icon->SetSize(2.8+(timer/10), 2.8 +(timer/10));
}

void Title::Draw(sf::RenderWindow& window)
{
	if (titleOn)
	{
		SpriteGo::Draw(window);
		icon->SetOrigin(Origins::MC);
		icon->SetPosition(1920 / 2.f, 1080.f / 3.f);
		icon->Draw(window);
		if (wordBlink)
		{
			window.draw(pressEnt);
		}
		
	}
	
}
