#pragma once
#include "Scene.h"

class UiHud;
class Player;
class Zombie;
class TileMap;
class Item;
class TileMap;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tilemap = nullptr;
	Zombie* boss = nullptr;


	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;
	bool isActive = true;

	//wave ����
	int WaveCount = 0;//������̺�
	int ZombieToSpawn = 0;
	int ZombieSpawned = 0;
	int ZombieRemaining = 0;
	int TileSize = 0;
	float SpawnTimer = 0.f;
	float SpawnInterval = 1.f;
	float ItemSpawnTimer = 0.f;//t�ð����ٴþ
	float ItemSpawnInterval = 2.f;//2�ʶ�°�����


	UiHud* uihud = nullptr;

public:
	SceneGame();
	~SceneGame() override = default;

	const std::list<Zombie*> GetZombies() const
	{
		return zombieList;
	}

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);

	void OnZombieKilled();// ����0�����Ǹ� �������̺� üũ��
	void SpawnBoss(int maxHp, float speed, int damage, float attackInterval, std::string texid);
	void SpawnItems(int count);
};