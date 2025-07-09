#include "stdafx.h"
#include "Wave.h"
#include "SceneGame.h"
#include "Framework.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
Wave::Wave(const std::string& name)
	: Wave(name)
{
}

void Wave::Init()
{
	WaveCount = 0;
	WaveNewZombie = 0;
	WaveZombie = 0;
	NextWave = false;

}

void Wave::Release()
{
}

void Wave::Update(float dt)
{
	
}

void Wave::Draw(sf::RenderWindow& window)
{
}

void Wave::StartNextWave()
{
	WaveCount++;
	WaveNewZombie = 10 + WaveCount * 5;

	SceneGame* SpawnZombies(WaveNewZombie);
}

bool Wave::IsWaveClear() const
{
	return false;
}

int Wave::GetWaveCount() const
{
	return WaveCount;
}

void Wave::ZombieDied()
{
}
