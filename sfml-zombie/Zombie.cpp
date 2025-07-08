#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

//Zombie::Zombie(int maxHp, float speed, int damage, float attackInterval, std::string texid)
//{
//	status.StatusmaxHp = maxHp;
//	status.Statusspeed = speed;
//	status.Statusdamage = damage;
//	status.StatusattackInterval = attackInterval;
//	status.texid = texid;
//}

Zombie::Zombie(int maxHp, float speed, int damage, float attackInterval, std::string texid)
	:maxHp(maxHp), speed(speed), damage(damage), attackInterval(attackInterval), texId(texid)
{
}



void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId), true);

	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	if (type == Types::Boss) {
	  SetScale({ 3.f, 3.f });
	}
	else
	SetScale({ 1.f, 1.f });

	hp = maxHp;
	attackTimer = 0.f;
}

void Zombie::Update(float dt)
{
	//std::cout << "거리 : " << Utils::Distance(player->GetPosition(), GetPosition()) << std::endl;
	if (Utils::Distance(player->GetPosition(), GetPosition()) <= 5) {
		dir = { 0.f, 0.f };
	}
	else {
		dir = Utils::GetNormal(player->GetPosition() - GetPosition());
		SetRotation(Utils::Angle(dir));
		SetPosition(GetPosition() + dir * speed * dt);
	}
	hitbox.UpdateTransform(body, GetLocalBounds());

	attackTimer += dt;
	if (attackTimer > attackInterval) {
		if (Utils::CheckCollision(hitbox.rect, player->GetHitBox().rect)) {
			player->OnDamage(damage);
			attackTimer = 0.f;
		}

	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 200;
		speed = 50.f;
		damage = 10.f;
		attackInterval = 1.f;
		break;
	case Types::Chase:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 100.f;
		damage = 3.f;
		attackInterval = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 200.f;
		damage = 5.f;
		attackInterval = 1.f;
		break;
	/*case Types::Boss:
		texId = "graphics/bloater.png";
		maxHp = 500;
		speed = 200.f;
		damage = 20.f;
		attackInterval = 0.8f;
		break;*/
	default:
		std::cout << "속도 : " << maxHp << std::endl;
		//speed = customSpeed;
		/*texId = status.texid;
		maxHp = status.StatusmaxHp;
		speed = status.Statusspeed;
		damage = status.Statusdamage;
		attackInterval = status.StatusattackInterval;*/
		break;
	}

}

void Zombie::OnDamage(int d)
{
	hp = Utils::Clamp(hp - d, 0, maxHp);
	if (hp == 0) {
		SetActive(false);
	}

}
