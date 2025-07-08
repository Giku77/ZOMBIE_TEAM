#include "stdafx.h"
#include "SceneTitle.h"
SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	Scene::Init();

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	fontIds.push_back("fonts/zombiecontrol.ttf");
	texIds.push_back("graphics/background.png");

	//uihud = (UiHud*)AddGameObject(new UiHud());
	//uihud->AddFontId("fonts/zombiecontrol.ttf");
	//uihud->AddMessage("ZOMBIE GAME");
	//uihud->SetPosition({ bounds.width * 0.5f, bounds.top - 20.f });

	SpriteGo* backgrounds = new SpriteGo("graphics/background.png", "background");
	backgrounds->SetTextureId("graphics/background.png");
	AddGameObject(backgrounds);

}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::Exit()
{
	Scene::Exit();
}
