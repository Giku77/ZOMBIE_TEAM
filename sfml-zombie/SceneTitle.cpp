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
	font.loadFromFile("fonts/zombiecontrol.ttf");

	titleText.setFont(font);
	titleText.setString("ZOMBIE GAME");
	titleText.setPosition({ 190.f , bounds.top + 200.f });
	titleText.setCharacterSize(120);


	float startTextX = 190.f;
	float startTextY = bounds.top + 500.f;

	startText.setFont(font);
	startText.setString("Game Start");
	startText.setPosition({ 190.f , bounds.top + 500.f });
	startText.setCharacterSize(120);

	startwidth = startRect.getLocalBounds().width;
	startHeight = startRect.getLocalBounds().height;
	startRect.setFillColor(sf::Color::Transparent);
	startRect.setOutlineColor(sf::Color::Yellow);
	startRect.setOutlineThickness(1.f);
	startRect.setSize({ startHeight, startwidth });

	float exitTextX = 190.f;
	float exitTextY = bounds.top + 800.f;
	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setPosition({ exitTextX, exitTextY });
	exitText.setCharacterSize(120);

	exitwidth = exitRect.getLocalBounds().width;
	exitHeight = exitRect.getLocalBounds().height;
	exitRect.setSize({ exitwidth,exitHeight });
	exitRect.setPosition({ exitTextX, exitTextY });
	exitRect.setFillColor(sf::Color::Transparent);
	exitRect.setOutlineColor(sf::Color::Yellow);
	exitRect.setOutlineThickness(1.f);

	//uihud = (UiHud*)AddGameObject(new UiHud());
	//uihud->AddFontId("fonts/zombiecontrol.ttf");
	//uihud->AddMessage("ZOMBIE GAME");
	//uihud->SetPosition({ bounds.width * 0.5f, bounds.top - 20.f });

	SpriteGo* backgrounds = new SpriteGo("graphics/background.png", "background");
	backgrounds->SetTextureId("graphics/background.png");
	AddGameObject(backgrounds);

	isExitClick = false;
	isStartClick = false;
	isDrawStartRect = false;
	isDrawExitRect = false;
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	/*if (
		InputMgr::GetMousePosition().x >= startRect.getPosition().x - 50.f
		&& InputMgr::GetMousePosition().x <= startRect.getPosition().x + startwidth + 50.f
		&& InputMgr::GetMousePosition().y >= startRect.getPosition().y - 50.f
		&& InputMgr::GetMousePosition().y <= startRect.getPosition().y + startHeight + 50.f
		)
	{
		isDrawStartRect = true;
		if (InputMgr::GetMouseButtonDown)
		{
			isStartClick = true;
		}
	}

	if (
		InputMgr::GetMousePosition().x >= exitRect.getPosition().x - 50.f
		&& InputMgr::GetMousePosition().x <= exitRect.getPosition().x + exitwidth + 50.f
		&& InputMgr::GetMousePosition().y >= exitRect.getPosition().y - 50.f
		&& InputMgr::GetMousePosition().y <= exitRect.getPosition().y + exitHeight + 50.f
		)
	{
		std::cout << exitRect.getPosition().x << ",";
		std::cout << exitRect.getPosition().y << std::endl;
		std::cout << "마우스 위치: " << InputMgr::GetMousePosition().x << std::endl;
		isDrawExitRect = true;
		if (InputMgr::GetMouseButtonDown)
		{
			isExitClick = true;
		}
	}*/

	sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(FRAMEWORK.GetWindow()));
	bool isStartMouseOver = Utils::PointInTransformBounds(startText, startText.getLocalBounds(), mouseWorldPos);
	bool isExitMouseOver = Utils::PointInTransformBounds(exitText, exitText.getLocalBounds(), mouseWorldPos);

	if (isStartMouseOver)
	{
		startText.setFillColor(sf::Color::Red);
		startText.setScale({ 1.1f,1.1f });
		if (InputMgr::GetMouseButtonDown)
		{
			isStartClick = true;
		}
	}
	else
	{
		startText.setFillColor(sf::Color::White);
		startText.setScale({ 1.f,1.f });
	}

	if (isExitMouseOver)
	{
		exitText.setFillColor(sf::Color::Red);
		exitText.setScale({ 1.1f,1.1f });
		if (InputMgr::GetMouseButtonDown)
		{
			isExitClick = true;
		}
	}
	else
	{
		exitText.setFillColor(sf::Color::White);
		exitText.setScale({ 1.f,1.f });
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
		SceneMgr::ChangeScene(SceneIds::Game);
		isStartClick = false;
	}

	if (isExitClick)
	{
		SceneMgr::ChangeScene(SceneIds::Game);
		isExitClick = false;
	}
}

void SceneTitle::Exit()
{
	Scene::Exit();
}