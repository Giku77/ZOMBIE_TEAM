#pragma once
#include "Scene.h"
class Zombie;
class Player;
class Wave :public Scene
{

protected:
	int WaveCount = 0;//현재웨이브
	int WaveNewZombie = 0;// 웨이브 시작시 총 좀비 소환몹수
	int WaveZombie = 0;// 웨이브 좀비
	bool NextWave = false;//좀비없으면 ture로바뀌고 담스테이지넘어가게
	

public:
	Wave(const std::string& name = "");
	virtual ~Wave() = default;

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void StartNextWave();// 시작시 
	bool IsWaveClear() const;// 좀비없는지 체크
	void ZombieDied();// 좀비 한 마리 죽었을 때 호출
	void SpawnZombies(int count);// 좀비 소환
	int GetWaveCount() { return WaveCount; }



};

