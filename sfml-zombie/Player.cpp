#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "TileMap.h"

Player::Player(const std::string& name)
	:GameObject(name)
{
}

Player::Player(const std::string& name, TileMap* t)
	:GameObject(name), tile(t)
{
}

void Player::SetPosition(const sf::Vector2f& pos) {
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}
void Player::SetRotation(float rot) {
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}
void Player::SetScale(const sf::Vector2f& s) {
	GameObject::SetScale(s);
	body.setScale(s);
}
void Player::SetOrigin(const sf::Vector2f& o) {
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}
void Player::SetOrigin(Origins preset) {
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom) Utils::SetOrigin(body, preset);
}


void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	tile = (TileMap*)SCENE_MGR.GetCurrentScene()->FindGameObject("TileMap");
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) {
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else sceneGame = nullptr;

	for (Bullet* b : bulletList) {
		b->SetActive(false);
		bulletPool.push_back(b);
	}
	bulletList.clear();

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	dir = { 0.f, 0.f };
	look = { 1.0f, 0.f };
	shootTimer = 0.f;
	hp = maxHp;
	level = 1;
	exp = 0.f;
	nextExp = 100.f;
	speed = 500.f;
	isAz = false;
	collided = false;
	InputMgr::isTyping = false;
}

void Player::Update(float dt)
{
	auto it = bulletList.begin();
	while (it != bulletList.end()) {
		if (!(*it)->GetActive()) {
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else {
			++it;
		}
	}
 

	//std::cout << "플레이어 위치: " << GetPosition().x << " / " << GetPosition().y << std::endl;
	//Pos
	if (!isAz) {
		dir.x = InputMgr::GetAxis(Axis::Horizontal);
		dir.y = InputMgr::GetAxis(Axis::Vertical);
		prevPos = GetPosition();

		if (Utils::Magnitude(dir) > 1.f) {
			Utils::Normalize(dir); //대각선 이동에서 정규화로 1로 크기 조절 필요
		}

		SetPosition(position + dir * speed * dt);
	}
	else {
		//dir = { 0.f, 0.f };
		if (!InputMgr::isTyping) {
			std::cout << "==== 특정 패턴 진입 ====" << std::endl;
			std::cout << "입력 : " << InputMgr::Getshuffled() << std::endl;
			InputMgr::isTyping = true;
		}
	}

	for (auto& w : tile->wallRects) {
		sf::FloatRect wallRect = Utils::TransformRect(tile->GetTransform(), w);

		if (wallRect.intersects(GetGlobalBounds())) {
			collided = true;
			break;
		}
	}

	if (collided) {
		SetPosition(prevPos);
		collided = false;
	}
	
	/*if (!InputMgr::isTyping) {
		isAz = false;
	}*/

	
	//Rot
	sf::Vector2i mousePos = InputMgr::GetMousePosition();

	sf::Vector2f mouseWPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWPos - GetPosition());
	//look = Utils::GetNormal((sf::Vector2f)InputMgr::GetMousePosition() - GetPosition());
	SetRotation(Utils::Angle(look));


	hitbox.UpdateTransform(body, GetLocalBounds());

	shootTimer += dt;
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer > shootInterval) {
		shootTimer = 0.f;
		shoot();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R)) {
		int sumAmmo = 30 - ammo;
		ammo += maxAmmo;
		if (ammo > 30) ammo = 30;
		maxAmmo -= sumAmmo;
		if (maxAmmo < 0) maxAmmo = 0;
	}

	if (exp > nextExp) {
		level++;
		exp -= nextExp;
		nextExp = 100 * pow(1.15, level - 1);
	}
	showPer = (exp / nextExp) * 100.f;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Player::shoot()
{
	std::cout << "플레이어의 총알 : " << ammo <<  " / " << maxAmmo << std::endl;
	std::cout << "플레이어의 레벨 : " << level <<  std::endl;
	std::cout << "플레이어의 경험치 : " << exp << " / " << nextExp << std::endl;
	std::cout << "플레이어의 경험치 퍼센트 : " << showPer << std::endl;
	if (ammo > 0) {
		Bullet* bullet = nullptr;
		if (bulletPool.empty()) {
			bullet = new Bullet();
			bullet->Init();
		}
		else {
			bullet = bulletPool.front();
			bulletPool.pop_front();
			bullet->SetActive(true);
		}
		bullet->Reset();
		bullet->Fire(position + look * 10.f, look, 1000.f, 200);

		bulletList.push_back(bullet);
		sceneGame->AddGameObject(bullet);
		ammo--;
	}
}

void Player::OnDamage(int d) {
	if (!isAlive()) return;

	hp = Utils::Clamp(hp - d, 0, maxHp);
	std::cout << "플레이어의 체력 : " << hp << std::endl;
	if (!isAlive()) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}