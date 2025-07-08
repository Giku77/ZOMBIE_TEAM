#pragma once
#include "Scene.h"
class SceneTitle :
	public Scene
{
protected:
	sf::RectangleShape startRect;
	sf::RectangleShape exitRect;

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
	bool isDrawStartRect;
	bool isDrawExitRect;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

