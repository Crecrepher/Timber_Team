#include "Tree.h"
#include "Utils.h"
#include "InputMgr.h"

Tree::Tree(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), countOfBranches(6), branches(countOfBranches), branchPositions(countOfBranches), currentBranch(0), logSizeX(1.f), logSizeY(1.f)
{
	texBranch.loadFromFile("graphics/branch.png");
	texLog.loadFromFile("graphics/log.png");

	for (auto& branch : branches)
	{
		branch = new Branch(texBranch, { -1.f, -1.f}, "Branch");
		branch->SetTree(this);
	}

	for (int i = 0; i < 100; ++i)
	{
		EffectGo* newGo = new EffectGo(texLog);
		newGo->SetActive(false);
		logPool.push_back(newGo);
	}
}

Tree::~Tree()
{

}

void Tree::InitBranches()
{
	currentBranch = 0;

	float x = GetPosition().x;
	float y = 800.f;
	float offset = branches[0]->GetSize().y + 100;

	for (int i = 0; i < branchPositions.size(); ++i)
	{
		branchPositions[i].x = x;
		branchPositions[i].y = y;
		y -= offset;
	}

	for (int i = 0; i < branchPositions.size(); ++i)
	{
		branches[i]->Init();
		branches[i]->SetPosition(branchPositions[i]);
		Sides side = (Sides)Utils::RandomRange(0, 1);
		branches[i]->SetSide(side);
		
	}
}

void Tree::Init()
{
	SpriteGo::Init();
//<<<<<<< HEAD
//	auto it = logEffects.begin();
//	while (it != logEffects.end())
//	{
//		logPool.push_back(*it);
//		it = logEffects.erase(it);
//	}
//=======
//>>>>>>> dfcc58bca3b4a1c889727b2834d343b2ac3f5a74
}

void Tree::Release()
{
	SpriteGo::Release();

	for (auto& branch : branches)
	{
		delete branch;
		branch = nullptr;
	}
	branches.clear();

	for (auto& effect : logPool)
	{
		delete effect;
		effect = nullptr;
	}
	logPool.clear();

	for (auto& effect : logEffects)
	{
		delete effect;
		effect = nullptr;
	}
	logEffects.clear();
}

void Tree::Update(float dt)
{
	SpriteGo::Update(dt);

	/*if (InputMgr::GetKeyDown(sf::Keyboard::Right) &&
		!InputMgr::GetKey(sf::Keyboard::Left) ||
		InputMgr::GetKeyDown(sf::Keyboard::Left) && 
		!InputMgr::GetKey(sf::Keyboard::Right))
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			sf::Vector2f pos = GetPosition();
			pos.y = GetSize().y;
			ShowEffectLog(Sides::Left, pos);

		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			sf::Vector2f pos = GetPosition();
			pos.y = GetSize().y;
			ShowEffectLog(Sides::Right, pos);
		}

		UpdateBranches();
	}*/
	

	auto it = logEffects.begin();
	while (it != logEffects.end())
	{
		if ((*it)->GetActive())
		{
			(*it)->Update(dt);
			++it;
		}
		else
		{
			logPool.push_back(*it);
			it = logEffects.erase(it);
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	for (auto branch : branches)
	{
		branch->Draw(window);
	}
	for (auto effect : logEffects)
	{
		effect->Draw(window);
	}
}

void Tree::UpdateBranches()
{
	currentBranch = (currentBranch + 1) % branches.size();
	// 1
	for (int i = 0; i < branches.size(); ++i)
	{
		int index = (currentBranch + i) % branches.size();
		branches[index]->SetPosition(branchPositions[i]);
		if (i == branches.size() - 1)
		{
			Sides side = (Sides)Utils::RandomRange(0, 1);
			branches[index]->SetSide(side);
		}
	}
}

void Tree::ShowEffectLog(Sides side, sf::Vector2f position)
{
	if (logPool.empty())
	{
		std::cout << "Log Pool Empty" << std::endl;
		return;
	}

	EffectGo* log = logPool.front();
	logPool.pop_front();
	logEffects.push_back(log);

	log->SetActive(true);
	log->Init();
	log->SetPosition(position);
	log->Fire(sf::Vector2f(side == Sides::Right ? 1000.f : -1000.f, -1000.f));
}

sf::Vector2f Tree::GetBranchPos(int index)
{
	return branches[index]->GetPosition();
}

Sides Tree::GetBranchSides()
{
	return branches[currentBranch]->GetSide();
}

void Tree::SetSize(float xSize, float ySize)
{
	SpriteGo::SetSize(xSize, ySize);
}

void Tree::SetBranchSize(float xSize, float ySize)
{
	for(int i=0; i<countOfBranches; i++)
		branches[i]->SetSize(xSize, ySize);
}

void Tree::SetChopSize(float xSize, float ySize)
{
	for (auto& obj : logPool)
		obj->SetSize(xSize, ySize);
}

void Tree::GetKeyDownLeft()
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) || InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Right, pos);
	}
	UpdateBranches();
}

void Tree::GetKeyDownRight()
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Right) || InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Left, pos);

	}
	UpdateBranches();
}
