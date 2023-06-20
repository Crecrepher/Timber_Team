#pragma once
#include <SFML/Audio.hpp>
#include "EffectGo.h"
#include "Defines.h"
#include <vector>

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

	//----yl start----
	bool characterOn;
	bool twoPlayerOn;
	bool p1Selected;
	int characterIndex;

	/*std::vector<sf::Texture*> texPlayer;
	std::vector<SpriteGo*> player;*/
	std::vector<SpriteGo*> playerCard;

	sf::Texture texPlayerCard;
	sf::Texture texPlayer1;
	sf::Texture texPlayer2;
	sf::Texture texPlayer3;
	sf::Texture texPlayer4;

	SpriteGo* player1;
	SpriteGo* player2;
	SpriteGo* player3;
	SpriteGo* player4;
	//SpriteGo* playerCard;

	sf::RectangleShape p1CharacterSelector;
	sf::RectangleShape p2CharacterSelector;

	std::string player1File;
	std::string player2File;

	//----yl end----


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
	std::string GetplayerFile(int pNum);

};

