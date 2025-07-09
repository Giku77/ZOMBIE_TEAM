#pragma once
#include "Scene.h"
class SceneChoose :
    public Scene
{
protected:
	SpriteGo* background1;
	sf::Text choose[6];

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	/*sf::Text choose2;
	sf::Text choose3;
	sf::Text choose4;
	sf::Text choose5;
	sf::Text choose6;*/

	sf::Font font;

public:
	SceneChoose();
	~SceneChoose() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	bool HandleTextHover(sf::Text& text, const sf::Vector2f& mousePos);
};

