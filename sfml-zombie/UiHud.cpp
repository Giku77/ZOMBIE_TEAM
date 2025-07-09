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
	for (auto& it : texts)
	{
		it.SetFontId(fontId);
	}
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

	for (int i = 0; i < count-1; i++) {
		levelpos = { levelBarHanKan.getPosition().x + startX + levelBarHanKan.getLocalBounds().width, levelBarHanKan.getPosition().y};
		levelBarHanKan.setPosition(levelpos);
		levelBar.push_back(levelBarHanKan);
	}
}



void UiHud::Init()
{
	levelBarHanKan.setSize({ 30.f, 15.f });
	levelBarHanKan.setFillColor(sf::Color::Green);
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
	//window.draw(levelBarHanKan);
	/*if (isShowMessage)
	{
		for (auto e : texts)
		{
			window.draw(e.GetText());
		}
	}*/


	for (auto it : levelBar)
	{
		window.draw(it);
	}
	/*for (int i = 0; i < levelBarDrawCount; i++)
	{
		std::cout << "레벨바 그리기" << std::endl;
		window.draw(levelBar[i]);
	}*/
}