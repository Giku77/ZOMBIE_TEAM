#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name), texts(0), textPos(0), textString('0'), levelBar(0), hpBar(0), levelBarHanKan({ 0,0 })
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
		std::cout << "폰트 파일 로드 실패" << std::endl;
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

void UiHud::SetLevelBar(float l)
{
	float exp = round(l);
	int count = (int)exp / 5;
	int startX = 3.f;

	levelBar.clear();
	if (l > 0) {
		levelpos = { FRAMEWORK.GetWindowBounds().width / 2.f - 330.f, FRAMEWORK.GetWindowBounds().height - 50.f };
		levelBarHanKan.setPosition(levelpos);
		levelBar.push_back(levelBarHanKan);
	}

	for (int i = 0; i < count - 1; i++) {
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
	levelpos = { FRAMEWORK.GetWindowBounds().left + 500.f,FRAMEWORK.GetWindowBounds().height - 50.f };

	levelBarHanKan.setPosition({ levelpos.x,levelpos.y });
	levelBar.push_back(levelBarHanKan);

	waveText.setPosition({ FRAMEWORK.GetWindowBounds().width - 180.f,FRAMEWORK.GetWindowBounds().top + 50.f });
	hpText.setPosition({ FRAMEWORK.GetWindowBounds().left + 50.f,FRAMEWORK.GetWindowBounds().top + 50.f });
	levelText.setPosition({ FRAMEWORK.GetWindowBounds().left + 50.f,FRAMEWORK.GetWindowBounds().top + 100.f });

	waveText.setString("wave:"+std::to_string(wavecount));
	hpText.setString("hp:"+std::to_string(hp));
	levelText.setString("level:"+std::to_string(level));

	waveText.setCharacterSize(40);
	hpText.setCharacterSize(40);
	levelText.setCharacterSize(40);

	waveText.setFillColor(sf::Color::White);
	hpText.setFillColor(sf::Color::White);
	levelText.setFillColor(sf::Color::White);

	texts.push_back(levelText);
	texts.push_back(hpText);
	texts.push_back(waveText);

	for (int i = 0; i < 3; i++)
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
}

void UiHud::Draw(sf::RenderWindow& window)
{
	for (auto e : texts)
	{
		window.draw(e);
	}
	
	for (int i = 0; i < 1; i++)
	{
		//std::cout << "레벨바 그리기" << std::endl;
		window.draw(levelBarHanKan);
	}
}

