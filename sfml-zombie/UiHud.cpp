#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name), texts(0), textPos(0), textString('0'), levelBar(0), levelBarHanKan({ 0,0 })
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	textPos.push_back(pos);
}

void UiHud::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
}

void UiHud::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
}

void UiHud::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	//if (preset != Origins::Custom)
	//{
	//	Utils::SetOrigin(gameObject, preset);
	//}
}

void UiHud::SetCharacterSize(int size)
{
}


void UiHud::AddFontId(const sf::String fontId)
{
	if (!font.loadFromFile("fonts/zombiecontrol.ttf"))
	{
		std::cout << "?��?�� 로드 불�??" << std::endl;
	}
	//for (int i =0; i<500; i++)
	//{
	//	font.loadFromFile("fonts/zombiecontrol.ttf");
	//	texts[i].setFont(font);
	//}
}

void UiHud::AddMessage(const sf::String Message)
{
	textString.push_back(Message);
}

void UiHud::SetHpBar(int currentHp, int maxHp, const sf::Vector2f& pos)
{
	monsterHpBars.clear();

	if (currentHp <= 0)
		return;

	const float barWidth = 100.f;   
	const float barHeight = 10.f;
	float hpPercent = Utils::Clamp01(static_cast<float>(currentHp) / static_cast<float>(maxHp));

	// ��� (ȸ��) ü�¹�
	sf::RectangleShape backgroundBar;
	backgroundBar.setSize({ barWidth, barHeight });
	backgroundBar.setFillColor(sf::Color(50, 50, 50)); // ��ο� ȸ��
	backgroundBar.setPosition(pos + sf::Vector2f(-barWidth / 2.f, -50.f)); // ��ü �������� ������
	monsterHpBars.push_back(backgroundBar);

	// ���� ü�� (������) ü�¹�
	sf::RectangleShape hpBar;
	hpBar.setSize({ barWidth * hpPercent, barHeight });
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(backgroundBar.getPosition());
	monsterHpBars.push_back(hpBar);
}

void UiHud::SetLevelBar(float l)
{
	float exp = round(l);
	int count = (int)exp / 5;
	int startX = 3.f;

	levelBar.clear();

	if (l > 0)
	{
		levelpos = { FRAMEWORK.GetWindowBounds().width / 2.f - 330.f, FRAMEWORK.GetWindowBounds().height - 50.f };
		levelBarHanKan.setPosition(levelpos);
		levelBar.push_back(levelBarHanKan);
	}

	for (int i = 0; i < count - 1; i++)
	{
		levelpos = { levelBarHanKan.getPosition().x + startX + levelBarHanKan.getLocalBounds().width, levelBarHanKan.getPosition().y };
		levelBarHanKan.setPosition(levelpos);
		levelBar.push_back(levelBarHanKan);
	}
}

void UiHud::Init()
{
	font.loadFromFile("fonts/zombiecontrol.ttf");
	levelBarHanKan.setSize({ 30.f, 15.f });
	levelBarHanKan.setFillColor(sf::Color::Green);
	
	GameOverText.setPosition({ 310.f ,600.f });
	GameOverText.setCharacterSize(150);
	GameOverText.setString("Game over");

	waveText.setPosition({ FRAMEWORK.GetWindowBounds().width - 180.f,FRAMEWORK.GetWindowBounds().top + 50.f });
	hpText.setPosition({ FRAMEWORK.GetWindowBounds().left + 50.f,FRAMEWORK.GetWindowBounds().top + 50.f });
	levelText.setPosition({ FRAMEWORK.GetWindowBounds().left + 50.f,FRAMEWORK.GetWindowBounds().height - 100.f });
	bulletText.setPosition({ FRAMEWORK.GetWindowBounds().left + 50.f,FRAMEWORK.GetWindowBounds().top + 100.f });
	azText.setPosition({ FRAMEWORK.GetWindowBounds().width / 2.f - 20.f,FRAMEWORK.GetWindowBounds().top + 300.f });

	waveText.setCharacterSize(40);
	hpText.setCharacterSize(40);
	levelText.setCharacterSize(40);
	bulletText.setCharacterSize(40);
	azText.setCharacterSize(40);

	waveText.setFillColor(sf::Color::White);
	hpText.setFillColor(sf::Color::White);
	levelText.setFillColor(sf::Color::White);
	bulletText.setFillColor(sf::Color::White);
	azText.setFillColor(sf::Color::White);

	texts.push_back(waveText);
	texts.push_back(hpText);
	texts.push_back(levelText);
	texts.push_back(bulletText);
	texts.push_back(azText);

	for (int i = 0; i < texts.size(); i++)
	{
		texts[i].setFont(font);
	}
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
}

void UiHud::Update(float dt)
{
	texts[0].setString("wave:" + std::to_string(wavecount));
	texts[1].setString("hp:" + std::to_string(hp));
	texts[2].setString("level:" + std::to_string(level));
	texts[3].setString("bullet:" + std::to_string(bullet) + "/"+std::to_string(maxBullet));
	if (InputMgr::isTyping) {
		texts[4].setString(InputMgr::Getshuffled());
	} else texts[4].setString("");
}

void UiHud::Draw(sf::RenderWindow& window)
{
	for (auto e : texts)
	{
		window.draw(e);
	}

	for (auto v : levelBar)
	{
		window.draw(v);
	}

	for (auto s : monsterHpBars) 
	{
		window.draw(s);
	}
}
