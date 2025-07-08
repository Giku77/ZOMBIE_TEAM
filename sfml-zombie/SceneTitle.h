#pragma once
#include "Scene.h"
class SceneTitle :
	public Scene
{
protected:
	UiHud* uihud;
	sf::Text titleText;
	sf::Text startText;
	sf::Text exitText;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

