#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "SpriteGo.h"
#include "Branch.h"
#include "EffectGo.h"

class Tree : public SpriteGo
{
protected:
	const int countOfBranches;
	std::vector<Branch*> branches;
	std::vector<sf::Vector2f> branchPositions;
	int currentBranch;
	sf::Texture texBranch;

	std::list<EffectGo*> logPool;
	std::list<EffectGo*> logEffects;
	float logSizeX;
	float logSizeY;

	sf::Texture texLog;

public:
	Tree(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Tree() override;
	
	void InitBranches();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void UpdateBranches();
	void ShowEffectLog(Sides side, sf::Vector2f position);
	sf::Vector2f GetBranchPos(int index);
	Sides GetBranchSides();

	virtual void SetSize(float xSize, float ySize);
	void SetBranchSize(float xSize, float ySize);
	void SetChopSize(float xSize, float ySize);
	void GetKeyDownLeft();
	void GetKeyDownRight();
};

