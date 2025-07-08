#pragma once
#include "GameObject.h"
#include "TextGo.h"

class UiHud :
    public GameObject
{
protected:
	std::vector<TextGo> texts;

	std::vector<sf::Vector2f> textPos;
	std::vector<sf::String> textString;

	std::string fontId;
	sf::Font font;

	bool isShowMessage;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetCharacterSize(int size);
	void AddFontId(const sf::String id);
	void AddMessage(const sf::String Message);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

