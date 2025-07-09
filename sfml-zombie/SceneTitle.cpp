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
	texIds.push_back("graphics/backgroundchange.png");
	font.loadFromFile("fonts/zombiecontrol.ttf");

	titleText.setFont(font);
	titleText.setString("ZOMBIE \nGAME");
	titleText.setPosition({ 90.f , bounds.top + 210.f });
	titleText.setCharacterSize(150);
	titleText.setRotation(-10);

	startText.setFont(font);
	startText.setString("Game Start");
	startText.setPosition({310.f , bounds.top + 600.f });
	startText.setCharacterSize(80);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setPosition({ 430.f ,bounds.top + 800.f });
	exitText.setCharacterSize(80);

	background1 = new SpriteGo("graphics/background.png", "background");
	background2 = new SpriteGo("graphics/backgroundchange.png", "background2");
	background1->SetTextureId("graphics/background.png");
	background2->SetTextureId("graphics/backgroundchange.png");
	AddGameObject(background1);
	AddGameObject(background2);
	background2->SetActive(false);

	isExitClick = false;
	isStartClick = false;
	isDrawBackgroundChange = false;
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(FRAMEWORK.GetWindow()));
	bool isStartMouseOver = Utils::PointInTransformBounds(startText, startText.getLocalBounds(), mouseWorldPos);
	bool isExitMouseOver = Utils::PointInTransformBounds(exitText, exitText.getLocalBounds(), mouseWorldPos);

	if (isStartMouseOver)
	{
		isDrawBackgroundChange = true;
		startText.setFillColor(sf::Color::Yellow);
		startText.setScale({ 1.1f,1.1f });
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			isStartClick = true;
		}
	}
	else
	{
		isDrawBackgroundChange = false;
		startText.setFillColor(sf::Color::White);
		startText.setScale({ 1.f,1.f });
	}

	if (isExitMouseOver)
	{
		exitText.setFillColor(sf::Color::Yellow);
		exitText.setScale({ 1.1f,1.1f });
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			isExitClick = true;
		}
	}
	else
	{
		exitText.setFillColor(sf::Color::White);
		exitText.setScale({ 1.f,1.f });
	}

	if (isDrawBackgroundChange)
	{
		background1->SetActive(false);
		background2->SetActive(true);
	}
	else {
		background1->SetActive(true);
		background2->SetActive(false);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
	window.draw(titleText);
	window.draw(startText);
	window.draw(exitText);

	if (isStartClick)
	{
		SCENE_MGR.ChangeScene(SceneIds::Choose);
		isStartClick = false;
	}

	if (isExitClick)
	{
		FRAMEWORK.GetWindow().close();
	}
}

void SceneTitle::Exit()
{
	Scene::Exit();
}