#pragma once
#include "GameObject.h"
#include "TextGo.h"

class Zombie;

class UiHud :
	public GameObject
{
protected:
	Zombie* zombie = nullptr;
	std::vector<sf::Text> texts;

	std::vector<sf::Vector2f> textPos;
	std::vector<sf::String> textString;

	std::vector<sf::RectangleShape>levelBar;
	std::vector<sf::RectangleShape>monsterHpBars;

	sf::RectangleShape levelBarHanKan;

	sf::Vector2f levelBarSize;
	sf::Vector2f hpBarSize;

	sf::Vector2f levelpos;

	float levelguage = 0.f;
	float nextlevel = 0.f;
	int level = 0;
	int levelBarDrawCount = 0;
	int bullet = 0;
	int maxBullet=0;

	std::string fontId;
	sf::Font font;

	sf::Text levelText;
	sf::Text hpText;
	sf::Text waveText;
	sf::Text bulletText;
	sf::Text azText;

	sf::Text GameOverText;
	
	int hp;
	int wavecount;

	int monsterHp;

	bool isShowMessage;
	bool isShowLevel;

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
	void SetZombie(Zombie* z) { zombie = z; }

	void SetHpBar(int currentHp, int maxHp, const sf::Vector2f& pos);
	void SetLevelBar(float l);
	void SetLevel(int l) { level = l; };
	void SetHp(int l) { hp = l; };
	void SetWave(int l) { wavecount = l; };
	void SetBullet(int l, int maxl) { bullet = l; maxBullet = maxl; };
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
