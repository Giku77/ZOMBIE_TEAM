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
	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/speed_pickup.png");

	tile = (TileMap*)AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));

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

	std::cout << "zombiePool�� ������ : " << zombiePool.size() << std::endl;

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
	uihud->SetLevelBar(player->getPer());
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

	worldView.setCenter(player->GetPosition());

	/*for (auto w : tile->wallRects) {
		sf::FloatRect transformedRect = Utils::TransformRect(tile->GetTransform(), w);

		if (transformedRect.intersects(player->GetGlobalBounds())) {
			std::cout << "�浹 ����" << std::endl;
		}
	}*/

	/*sf::Vector2f nextPos = player->GetPosition();
	if (tile->GetBounds().contains(nextPos))
	{
		player->SetPosition(nextPos);
	}*/
	/*sf::FloatRect playerBounds = player->GetGlobalBounds();
	sf::FloatRect mapBounds = tile->GetBounds();

	if (mapBounds.contains(playerBounds.left, playerBounds.top) &&
		mapBounds.contains(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height))
	{
		std::cout << "��� Ȯ��" << std::endl;
	}*/

	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		SpawnZombies(10);
		std::cout << "���� �ִ� ���� �� : " << zombieList.size() << std::endl;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::LShift)) {
		SpawnItems(15);
		//SpawnBoss(500, 200.f, 20.f, 0.8f, "graphics/bloater.png");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace)) {
		SCENE_MGR.ChangeScene(SceneIds::Title);
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

		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);

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

		item->Reset();

		item->SetPosition(Utils::RandomInUnitCircle() * 1000.f);

		itemList.push_back(item);
	}
}

void SceneGame::Draw(sf::RenderWindow& window) {
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);
	if (uihud != nullptr) {
		uihud->Draw(window);
	}
}
