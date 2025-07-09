#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class Bullet;
class TileMap;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f dir;
	sf::Vector2f look;

	TileMap* tile = nullptr;

	float speed = 500.f;

	SceneGame* sceneGame = nullptr;
	HitBox hitbox;

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	float shootInterval = 0.1f;
	float shootTimer = 0.f;

	int hp = 0;
	int maxHp = 100;

	int ammo = 0;
	int maxAmmo = 0;

	int level = 1;
	float exp = 0.f;
	float nextExp = 100.f;

	float showPer = 0.f;

	bool isAz = false;
	bool collided = false;
	sf::Vector2f prevPos;

public:
	sf::Vector2f velocity = dir * speed;
	float getPer() const { return showPer; }
	int getLv() const { return level; }
	int getHp() const { return hp; }
	bool isAlive() const { return hp > 0; }

	void AddExp(float f) { exp += f; }


	void SetisAz(bool r) { isAz = r; }
	bool GetisAz() { return isAz; }

	void SetAmmo(int a) {
		maxAmmo += a;
		if (maxAmmo > 100) maxAmmo = 100;
	}
	int GetAmmo() const { return ammo; }
	int GetMaxAmmo() const { return maxAmmo; }

	Player(const std::string& name = "");
	Player(const std::string& name, TileMap* t);
	~Player() override = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	const sf::Sprite& getBody() const { return body; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override {
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override {
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const { return hitbox; }

	void shoot();
	void heal(int h) {
		hp += h;
		if (hp > maxHp) hp = maxHp;
	}
	void AddSpeed(float s) {
		speed += s;
	}
	void OnDamage(int d);
};