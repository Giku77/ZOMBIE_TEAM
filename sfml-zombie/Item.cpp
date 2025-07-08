#include "stdafx.h"
#include "Item.h"
#include "Player.h"

Item::Item(const std::string& name)
	: GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}


void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Item::Release()
{
}

void Item::Reset()
{
	if (GetName() == "Ammo" || type.type == ItemType::Type::Ammo) {
		SetItemType({ ItemType::Type::Ammo, "graphics/ammo_pickup.png" });
	}
	if (GetName() == "Heal" || type.type == ItemType::Type::Heal) {
		SetItemType({ ItemType::Type::Heal, "graphics/health_pickup.png" });
	}
	sprite.setTexture(TEXTURE_MGR.Get(type.texId), true);
	SetOrigin(Origins::MC);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void Item::Update(float dt)
{
	hitBox.UpdateTransform(sprite, GetLocalBounds());
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");
	if (Utils::CheckCollision(sprite, player->getBody())) {
		if ((GetName() == "Ammo" || type.type == ItemType::Type::Ammo) && GetActive()) {
			player->SetAmmo(20);
		}
		if ((GetName() == "Heal" || type.type == ItemType::Type::Heal) && GetActive()) {
			player->heal(30);
		}
		SetActive(false);
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}