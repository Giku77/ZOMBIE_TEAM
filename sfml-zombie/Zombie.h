#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;
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

	//struct Status 
	//{
	//	int StatusmaxHp = 0;
	//	float Statusspeed = 0.f;
	//	int Statusdamage = 0;
	//	float StatusattackInterval = 0.f;
	//	std::string texid;
	//};

	static const int TotalTypes = 3;

protected:
	Types type = Types::Bloater;
	//Status status;
	Player* player = nullptr;


	sf::Sprite body;
	std::string texId;

	sf::Vector2f dir;

	int maxHp = 0;
	int hp = 0;
	int damage = 0;
	float attackInterval = 0.f;
	float attackTimer = 0.f;

	float speed = 0.f;
	float customSpeed = 0.f;

	HitBox hitbox;

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
};

