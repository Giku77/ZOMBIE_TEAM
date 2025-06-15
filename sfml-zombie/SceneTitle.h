#pragma once
#include "Scene.h"
class SceneTitle :
	public Scene
{
protected:
	SpriteGo* background1;
	SpriteGo* background2;

	sf::Text titleText;
	sf::Text startText;
	sf::Text exitText;
	
	float startwidth;
	float startHeight;
	float exitwidth;
	float exitHeight;

	sf::Font font;

	bool isExitClick;
	bool isStartClick;
	bool isDrawBackgroundChange;

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	sf::Sprite backgroundSprite2;
	sf::Texture backgroundTexture2;

public:
	SceneTitle();
	~SceneTitle() = default;
	
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

