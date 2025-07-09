#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "SpriteGo.h"
#include "Blood.h"
#include "SceneGame.h"
Zombie::Zombie(const std::string& name)
	: GameObject(name)
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
	SetScale({ 1.f, 1.f });

	hp = maxHp;
	attackTimer = 0.f;
	hpAdd = 1;
	speedAdd = 0.1f;
}

void Zombie::Update(float dt)
{
	//std::cout << "°Å¸® : " << Utils::Distance(player->GetPosition(), GetPosition()) << std::endl;

	if (Utils::Distance(player->GetPosition(), GetPosition()) <= 5 || shotTimer > 0.f) {
		//speed = 0.f;
		if (shotTimer > 0.f)
		{

			shotTimer -= dt;
		}
		dir = { 0.f, 0.f };
		///*if (Utils::CheckCollision(player->getBody(), body)) {
		//	dir = Utils::GetNormal(player->GetPosition() - GetPosition());
		//	dir.x *= -1.f;
		//	dir.y *= -1.f;
		//	SetRotation(Utils::Angle(dir));
		//	SetPosition(GetPosition() + dir * speed * dt);
		//}*/
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
	Addtimer += dt;
	if (Addtimer > 10.f && Addtimer < 12.f)
	{

		hpAdd += 10;
		speed += speedAdd;
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
		speed = 5.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	case Types::Chase:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 10.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 20.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	default:
		break;
	}

}

void Zombie::OnDamage(int d)
{
	hp = Utils::Clamp(hp - d, 0, maxHp);

	if (hp == 0)
	{
		OnDie();
	}
	else
	{
		shotTimer = 0.3f;
	}
}

void Zombie::OnDie()
{

	Blood* blood = new Blood();
	blood->SetTexture("graphics/blood.png");
	blood->SetPosition(GetPosition());
	blood->SetOrigin(Origins::MC);
	SCENE_MGR.GetCurrentScene()->AddGameObject(blood);
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (sceneGame)
		sceneGame->OnZombieKilled();
	SetActive(false);

}