#pragma once
#include "Scene.h"

class Uihud;
class Player;
class Zombie;
class Item;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* boss = nullptr;
	UiHud* uihud = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;

public:
	SceneGame();
	~SceneGame() override = default;

	const std::list<Zombie*> GetZombies() const {
		return zombieList;
	}

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
	void SpawnBoss(int maxHp, float speed, int damage, float attackInterval, std::string texid);
	void SpawnItems(int count);
};

