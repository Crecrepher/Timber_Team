#pragma once
#include <SFML/Audio.hpp>
#include "EffectGo.h"
#include "Defines.h"

class Title : public SpriteGo
{
private:
	bool titleOn;
	bool menuOn;
	bool wordBlink;
	bool Exiter;
	float timer;
	
	int menuIndex;

	sf::Font font;
	sf::Text pressEnt;

	sf::Texture texicon;
	EffectGo* icon;
	
	sf::Texture texbutton1;
	sf::Texture texbutton2;
	sf::Texture texbutton3;
	sf::Texture texscreenChop;

	sf::RectangleShape menuSelector;

	SpriteGo* button1;
	SpriteGo* button2;
	SpriteGo* button3;
	SpriteGo* screenChop;

	sf::SoundBuffer soundBufferChop;
	sf::SoundBuffer soundBufferDeath;

	sf::Sound soundChop;
	sf::Sound soundDeath;


public:
	Title(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Title();
	bool IsMenu() const;
	void MenuChange(bool in);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

