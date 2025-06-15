#include "stdafx.h"
#include "SceneTitle.h"
SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	fontIds.push_back("fonts/zombiecontrol.ttf");
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/backgroundchange.png");
	font.loadFromFile("fonts/zombiecontrol.ttf");

	titleText.setFont(font);
	titleText.setString("ZOMBIE \nGAME");
	titleText.setRotation(-10);
	titleText.setPosition({ 90.f , bounds.top + 210.f });
	titleText.setCharacterSize(150);

	startText.setFont(font);
	startText.setString("Game Start");
	startText.setPosition({ 310.f , bounds.top + 600.f });
	startText.setCharacterSize(80);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setPosition({430.f ,bounds.top + 800.f });
	exitText.setCharacterSize(80);

	//background1 = new SpriteGo("graphics/background.png");
	//background2 = new SpriteGo("graphics/backgroundchange.png");


	//FRAMEWORK.GetWindow().setView(FRAMEWORK.GetWindow().getDefaultView());
	//AddGameObject(background1);
	//AddGameObject(background2);
	//background2->SetActive(false);
	Scene::Init();

	backgroundTexture.loadFromFile("graphics/background.png");
	backgroundSprite.setTexture(backgroundTexture);

	backgroundTexture2.loadFromFile("graphics/backgroundchange.png");
	backgroundSprite2.setTexture(backgroundTexture2);
	//background1->Reset();
	isExitClick = false;
	isStartClick = false;
	isDrawBackgroundChange = false;
}

void SceneTitle::Enter()
{
	Scene::Enter();
	SOUND_MGR.Play();
	//FRAMEWORK.GetWindow().setView(uiView);
	sf::Vector2u texSize = TEXTURE_MGR.Get("graphics/background.png").getSize();
	std::cout << "��� �ؽ�ó ������: " << texSize.x << "x" << texSize.y << std::endl;
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
		startText.setScale({ 1.f,1.f });
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

	//if (isDrawBackgroundChange)
	//{
	//	background1->SetActive(false);
	//	background2->SetActive(true);
	//}
	//else {
	//	background1->SetActive(true);
	//	background2->SetActive(false);
	//}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	if (isDrawBackgroundChange)
		window.draw(backgroundSprite2);
	else
		window.draw(backgroundSprite);

	Scene::Draw(window);
	//window.setView(uiView);
	window.draw(titleText);
	window.draw(startText);
	window.draw(exitText);
	//if(!isDrawBackgroundChange) window.draw(backgroundSprite);
	//else window.draw(backgroundSprite2);

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