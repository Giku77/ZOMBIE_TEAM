#pragma once
#include "Scene.h"

class Player;
class Zombie;
class TileMap;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tilemap = nullptr;
	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	sf::Sprite cursor;
	bool isActive = true;

	//wave ����
	int WaveCount = 0;//������̺�
	int ZombieToSpawn = 0;
	int ZombieSpawned = 0;
	int ZombieRemaining = 0;
	int TileSize = 0;
	float SpawnTimer = 0;
	float SpawnInterval = 1.f;

	
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
};

