#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;
class SpriteGo;
class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chase,
		Crawler,
		Boss,
		Custom,
	};


	static const int TotalTypes = 3;

protected:
	Types type = Types::Bloater;
	//Status status;
	Player* player = nullptr;


	sf::Sprite body;

	std::string texId;
	std::string texbloodId;

	sf::Vector2f dir;

	int maxHp = 0;
	int hp = 0;
	int damage = 0;
	int hpAdd = 0;
	
	float attackInterval = 0.f;
	float attackTimer = 0.f;

	float speed = 0.f;
	float speedAdd = 0.f;
	float Addtimer = 0.f;
	float shotTimer = 0.f;
	
	SpriteGo* blood = nullptr;
	float bloodTimer = 0.f;
	bool bloodon = false;
	float customSpeed = 0.f;

	HitBox hitbox;

	bool isUseAZ = false;

public:
	Zombie(const std::string& name = "");
	Zombie(int maxHp, float speed, int damage, float attackInterval, std::string texid);
	virtual ~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
	void ChangeType(Types t) { type = t; }

	sf::FloatRect GetLocalBounds() const override {
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override {
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const { return hitbox; }
	void OnDamage(int d);
	void OnDie();// Á×´Â´Ù
	bool IsStunned() const { return shotTimer > 0.f; }
};

