#include "stdafx.h"
#include "SceneChoose.h"

SceneChoose::SceneChoose()
	: Scene(SceneIds::Choose)
{
}

void SceneChoose::Init()
{
	Scene::Init();
	/*
	increase rate of fire
	increased clif sizecnext reload
	increased max health
	increased run speed
	more and better health pickups
	more and better ammo pickups
	*/
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	float intervalY = 0.f;

	texIds.push_back("graphics/background.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");
	font.loadFromFile("fonts/zombiecontrol.ttf");

	backgroundTexture.loadFromFile("graphics/background.png");
	backgroundSprite.setTexture(backgroundTexture);

	/*background1 = new SpriteGo("graphics/background.png", "background");
	background1->SetTextureId("graphics/background.png");
	AddGameObject(background1);*/

	for (int i = 0; i < 6; i++)
	{
		intervalY += 120.f;
		choose[i].setFont(font);
		choose[i].setPosition({ 90.f , bounds.top + intervalY });
		choose[i].setCharacterSize(40);
	}
	choose[0].setString("1.increase rate of fire");
	choose[1].setString("2.increased clif sizecnext reload");
	choose[2].setString("3.increased max health");
	choose[3].setString("4.increased run speed");
	choose[4].setString("5.more and better health pickups");
	choose[5].setString("6.more and better ammo pickups");
}

void SceneChoose::Enter()
{
	Scene::Enter();
}

void SceneChoose::Update(float dt)
{
	Scene::Update(dt);
	sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(FRAMEWORK.GetWindow()));
	for (int i = 0; i < 6; i++)
	{
		if (HandleTextHover(choose[0], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(0);

		}
		if (HandleTextHover(choose[1], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(1);
		}
		if (HandleTextHover(choose[2], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(2);
		}
		if (HandleTextHover(choose[3], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(3);
		}
		if (HandleTextHover(choose[4], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(4);
		}
		if (HandleTextHover(choose[5], mouseWorldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
			SCENE_MGR.setType(5);
		}
	}
}

void SceneChoose::Exit()
{
	Scene::Exit();
}

void SceneChoose::Draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);

	Scene::Draw(window);
	for (int i = 0; i < 6; i++)
	{
		window.draw(choose[i]);
	}
}

bool SceneChoose::HandleTextHover(sf::Text& text, const sf::Vector2f& mousePos)
{
	bool isMouseOver = Utils::PointInTransformBounds(text, text.getLocalBounds(), mousePos);

	if (isMouseOver)
	{
		text.setFillColor(sf::Color::Yellow);
		text.setScale({ 1.1f, 1.1f });

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			return true;
		}
	}
	else
	{
		text.setFillColor(sf::Color::White);
		text.setScale({ 1.f, 1.f });
	}
	return false;
}
