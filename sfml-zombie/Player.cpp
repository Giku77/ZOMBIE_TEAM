#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"

Player::Player(const std::string& name)
	:GameObject(name)
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


	//Pos
	dir.x = InputMgr::GetAxis(Axis::Horizontal);
	dir.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(dir) > 1.f) {
		Utils::Normalize(dir); //대각선 이동에서 정규화로 1로 크기 조절 필요
	}
	SetPosition(position + dir * speed * dt);

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
		ammo += maxAmmo;
		if (ammo > 30) ammo = 30;
		maxAmmo -= ammo;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Player::shoot()
{
	std::cout << "플레이어의 총알 : " << ammo <<  " / " << maxAmmo << std::endl;
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
		bullet->Fire(position + look * 10.f, look, 1000.f, 10);

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