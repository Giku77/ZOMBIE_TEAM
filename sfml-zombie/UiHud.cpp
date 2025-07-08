#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
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

void UiHud::AddFontId(const sf::String fontId)
{

	if (!font.loadFromFile("fonts/zombiecontrol.ttf")) {
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

void UiHud::Init()
{

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
	if (isShowMessage)
	{
		for (auto e : texts)
		{
			window.draw(e.GetText());
		}
	}
}