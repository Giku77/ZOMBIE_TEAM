#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init() {
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");

	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/blood.png");


	tilemap =(TileMap*)AddGameObject(new TileMap("TileMap"));

	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; i++) {
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	WaveCount = 0;
	ZombieToSpawn = 10 + WaveCount * 5;
	ZombieSpawned = 0;
	ZombieRemaining = 0;
	SpawnTimer = 0;
	SpawnInterval = 1.f;

	Scene::Init();
}

void SceneGame::Exit() {
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (auto zombie : zombieList) {
		//RemoveGameObject(zombie);
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	std::cout << "zombiePool의 사이즈 : " << zombiePool.size() << std::endl;

	Scene::Exit();
}

void SceneGame::Enter() {

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame::Update(float dt) 
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	auto it = zombieList.begin();
	while (it != zombieList.end()) {
		if (!(*it)->GetActive()) {
			zombiePool.push_back(*it);
			it = zombieList.erase(it);
		}
		else {
			++it;
		}
	}
	

	// 웨이브 클리어 후 시작
	if (ZombieRemaining <= 0) 
	{
		if (tilemap != nullptr)
		{
			tilemap->Set({ 12 + WaveCount * 4,12 + WaveCount * 4 }, { 50.f,50.f });
			player->SetPosition({ 0.f+WaveCount *100, 0.f+ WaveCount * 100 });
		}
		WaveCount++;
		ZombieToSpawn = 10 + WaveCount * 3;
		ZombieSpawned = ZombieToSpawn;
		ZombieRemaining = ZombieToSpawn;
		SpawnZombies(ZombieSpawned);



		std::cout << "Wave " << WaveCount << " 시작!\n";
	}
	worldView.setCenter(player->GetPosition());
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0; i < count; i++) {
		Zombie* zombie = nullptr;
		if (zombiePool.empty()) {
			zombie = (Zombie*)AddGameObject(new Zombie());
			zombie->Init();
		}
		else {
			zombie = zombiePool.front();
			zombiePool.pop_front();
			zombie->SetActive(true);
		}


		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));

		zombie->Reset();	

		zombie->SetPosition(Utils::RandomPointInRect({ -300.f,-300.f, 
			600.f+ (WaveCount-1) * 200, 600.f + (WaveCount - 1) * 200 }));
	

		zombieList.push_back(zombie);
	}
}

void SceneGame::OnZombieKilled()
{
	ZombieRemaining--;
}

void SceneGame::Draw(sf::RenderWindow& window) 
{
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);
}
