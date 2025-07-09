#pragma once
#include "Scene.h"

class UiHud;
class Player;
class Zombie;
class Item;
class TileMap;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	Zombie* boss = nullptr;
	TileMap* tile = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;

	UiHud* uihud = nullptr;

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

