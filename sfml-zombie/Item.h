#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

struct ItemType {
	enum class Type { Ammo, Heal, Speed, Total };
	Type type;
	std::string texId;


	bool operator==(const ItemType& o) const {
		return type == o.type;
	}
};

class Item :
    public GameObject
{
protected:
	sf::Sprite sprite;
	ItemType type;

	HitBox hitBox;

	Player* player = nullptr;

public:
	Item(const std::string& name = "");
	virtual ~Item() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetItemType(const ItemType& t) { type = t; }
	void SetType(const ItemType::Type& t) { type.type = t; }
	const ItemType& GetItemType() const { return type; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

