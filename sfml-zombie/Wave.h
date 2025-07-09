#pragma once
#include "Scene.h"
class Zombie;
class Player;
class Wave :public Scene
{

protected:
	int WaveCount = 0;//������̺�
	int WaveNewZombie = 0;// ���̺� ���۽� �� ���� ��ȯ����
	int WaveZombie = 0;// ���̺� ����
	bool NextWave = false;//��������� ture�ιٲ�� �㽺�������Ѿ��
	

public:
	Wave(const std::string& name = "");
	virtual ~Wave() = default;

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void StartNextWave();// ���۽� 
	bool IsWaveClear() const;// ��������� üũ
	void ZombieDied();// ���� �� ���� �׾��� �� ȣ��
	void SpawnZombies(int count);// ���� ��ȯ
	int GetWaveCount() { return WaveCount; }



};

