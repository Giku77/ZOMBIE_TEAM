#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "SpriteGo.h"
#include "Blood.h"
#include "SceneGame.h"
#include "TileMap.h"
Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

//Zombie::Zombie(int maxHp, float speed, int damage, float attackInterval, std::string texid)
//	:status({ maxHp, speed, damage, attackInterval, texid })
//{
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
	tile = (TileMap*)SCENE_MGR.GetCurrentScene()->FindGameObject("TileMap");

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
	hpAdd = 1;
	speedAdd = 0.1f;
	isUseAZ = false;
}


void Zombie::Update(float dt)
{
	//std::cout << "거리 : " << Utils::Distance(player->GetPosition(), GetPosition()) << std::endl;

	    if (Utils::Distance(player->GetPosition(), GetPosition()) <= 5 || shotTimer > 0.f) {
		//speed = 0.f;
		if (shotTimer > 0.f)
		{
			shotTimer -= dt;
		}
			dir = { 0.f, 0.f };
			prevPos = GetPosition();
		}
		else {
			dir = Utils::GetNormal(player->GetPosition() - GetPosition());
			SetRotation(Utils::Angle(dir));
			SetPosition(GetPosition() + dir * speed * dt);
			prevPos = GetPosition();
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
		speed = 50.f;
		damage = 10.f;
		attackInterval = 1.f;
		break;
	case Types::Chase:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 10.f;
		damage = 100.f;
		speed = 100.f;
		damage = 3.f;
		attackInterval = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 20.f;
		damage = 100.f;
		speed = 200.f;
		damage = 5.f;
		attackInterval = 1.f;
		break;
	//case Types::Boss:
	//	/*texId = "graphics/bloater.png";
	//	maxHp = 500;
	//	speed = 200.f;
	//	damage = 10.f;
	//	attackInterval = 0.8f;*/
	//	break;
	default:
		//std::cout << "스피드 : " << speed << std::endl;
		break;
	}

}


void Zombie::OnDamage(int d)
{
	hp = Utils::Clamp(hp - d, 0, maxHp);
	std::cout << "좀비의 체력 : " << hp << std::endl;
	if (hp <= 250.f && type == Types::Boss && !isUseAZ) {
		if (player != nullptr && !player->GetisAz()) {
			player->SetisAz(true);
			speed = 100.f;
			isUseAZ = true;
		}
	}
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
	if (player != nullptr) {
		player->AddExp(Utils::RandomRange(1.f, 10.f));
		if (type == Types::Boss) player->AddExp(50.f);
	}
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

