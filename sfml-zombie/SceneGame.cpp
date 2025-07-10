#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Item.h"
#include "UiHud.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init() {
	//fontIds.push_back("fonts/zombiecontrol.ttf");

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");

	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/blood.png");

	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/speed_pickup.png");


	player = (Player*)AddGameObject(new Player("Player"));
	tilemap = (TileMap*)AddGameObject(new TileMap("TileMap"));

	for (int i = 0; i < 100; i++) {
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);

		Item* item = (Item*)AddGameObject(new Item());
		item->SetActive(false);
		itemPool.push_back(item);
	}

	uihud = new UiHud();
	uihud->Init();
	Scene::Init();
}

void SceneGame::Exit() {
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (auto zombie : zombieList) {
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	for (auto item : itemList) {
		item->SetActive(false);
		itemPool.push_back(item);
	}
	itemList.clear();


	Scene::Exit();
}

void SceneGame::Enter() {

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	WaveCount = 0;
	ZombieToSpawn = 10 + WaveCount * 5;
	ZombieSpawned = 0;
	ZombieRemaining = 0;
	SpawnTimer = 0;
	SpawnInterval = 1.f;
	ItemSpawnTimer = 0.f;
	ItemSpawnInterval = 2.f;

	if (tilemap != nullptr)
	{
		tilemap->Set({ 12 + WaveCount * 4, 12 + WaveCount * 4 }, { 50.f, 50.f });
		player->SetPosition({ WaveCount * 100.f, WaveCount * 100.f }); // WaveCount==0ÀÌ¸é (0,0)
	}

	Scene::Enter();

	SpawnItems(5);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame::Update(float dt)
{
	/*if ((int)SCENE_MGR.getType() == 0) {
		
	}*/


	//¾ÆÀÌÅÛ ·£´ý¼ÒÈ¯
	ItemSpawnTimer += dt;
	
	if (ItemSpawnTimer >= ItemSpawnInterval+ WaveCount*3)//0ÃÊ°¡ dt°ª¹Þ¾Æ¼­ ´Ã¾î³ª´Ù°¡ 2ÃÊ³Ñ¾î°¡¸é ½ºÅ¾
	{
		ItemSpawnTimer = 0.f;
		SpawnItems(Utils::RandomRange(1, 3) + 3 * WaveCount);
	}
	
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	uihud->SetLevelBar(player->getPer());
	uihud->SetHp(player->getHp());
	uihud->SetLevel(player->getLv());
	uihud->SetWave(WaveCount);
	uihud->SetBullet(player->GetAmmo(),player->GetMaxAmmo());
	if (boss != nullptr) {
		uihud->SetZombie(boss);
		uihud->SetHpBar(boss->GetHp(), 500, (sf::Vector2f)WorldToScreen(boss->GetPosition()));
	}
	uihud->Update(dt);
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


	if (ZombieRemaining <= 0)
	{
		WaveCount++;
		ZombieToSpawn = 10 + WaveCount * 3;
		ZombieSpawned = ZombieToSpawn;
		ZombieRemaining = ZombieToSpawn;
		SpawnZombies(ZombieSpawned);
		if (WaveCount % 5 == 0)
		{
			SpawnBoss(500, 200.f, 20.f, 0.8f, "graphics/bloater.png");
		}
		if (tilemap != nullptr)
		{
			if (WaveCount <= 4)
			{
				tilemap->Set({ 12 + WaveCount * 4,12 + WaveCount * 4 }, { 50.f,50.f });
				player->SetPosition({ 0.f + WaveCount * 100, 0.f + WaveCount * 100 });
				//std::cout << "ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ : " << player->GetPosition().x << " / " << player->GetPosition().y << std::endl;
			}
			if (WaveCount > 4)
			{
				tilemap->Set({ 28,28 }, { 50.f,50.f });
				player->SetPosition({ 400.f, 400.f });
			}

		}



		//std::cout << "Wave " << WaveCount << " ï¿½ï¿½ï¿½ï¿½!\n";
	}
	worldView.setCenter(player->GetPosition());



	/*if (InputMgr::GetKeyDown(sf::Keyboard::LShift)) {
		SpawnItems(15);
		SpawnBoss(500, 200.f, 20.f, 0.8f, "graphics/bloater.png");
	}*/

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace)) {
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}


}

void SceneGame::SpawnZombies(int count)
{

	for (int i = 0; i < count; i++)
	{
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

		if (WaveCount <= 4)
		{

			zombie->SetPosition(Utils::RandomPointInRect({ -250.f,-250.f,
				500.f + (WaveCount) * 200, 500.f + (WaveCount) * 200 }));

		}
		if (WaveCount > 4) {
			zombie->SetPosition(Utils::RandomPointInRect({ -250.f,-250.f,
				1300.f, 1300.f }));
		}

		zombieList.push_back(zombie);
	}
}


void SceneGame::SpawnBoss(int maxHp, float speed, int damage, float attackInterval, std::string texid)
{
	boss = (Zombie*)AddGameObject(new Zombie(maxHp, speed, damage, attackInterval, texid));
	boss->ChangeType(Zombie::Types::Boss);
	boss->Init();


	boss->Reset();
	boss->SetPosition(Utils::RandomInUnitCircle() * 500.f);

	zombieList.push_back(boss);
}

void SceneGame::SpawnItems(int count)
{
	for (int i = 0; i < count; i++) {
		Item* item = nullptr;
		if (itemPool.empty()) {
			item = (Item*)AddGameObject(new Item());
			item->Init();
		}
		else {
			item = itemPool.front();
			itemPool.pop_front();
			item->SetActive(true);
		}

		item->SetType((ItemType::Type)Utils::RandomRange(0, (int)ItemType::Type::Total));
		if ((int)SCENE_MGR.getType() == 4 && Utils::RandomValue() > 0.5f) {
			item->SetType(ItemType::Type::Heal);
		}
		if ((int)SCENE_MGR.getType() == 5 && Utils::RandomValue() > 0.5f) {
			item->SetType(ItemType::Type::Ammo);
		}

		item->Reset();

		if (WaveCount <= 4)
		{
			item->SetPosition(Utils::RandomPointInRect({ -250.f, -250.f,500.f + (WaveCount) * 200,
					500.f + (WaveCount) * 200 }));
		}
		if (WaveCount > 4)
		{
			item->SetPosition(Utils::RandomPointInRect({ -300.f,-300.f,
				1400.f, 1400.f }));
		}
		itemList.push_back(item);
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
	if (uihud != nullptr) {
		uihud->Draw(window);
	}
}
