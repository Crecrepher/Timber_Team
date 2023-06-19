#pragma once
#include "SpriteGo.h"
#include "Defines.h"

class Title : public SpriteGo
{
private:
	bool titleOn;
	bool wordBlink;
	float timer;
	
	sf::Font font;
	sf::Texture texicon;
	SpriteGo* icon;
	sf::Text pressEnt;

public:
	Title(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Title();
	bool IsTitle() const;
	void TitleChange(bool in);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

