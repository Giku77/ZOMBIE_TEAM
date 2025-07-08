#pragma once
class HitBox
{
protected:
public:
	sf::RectangleShape rect;

	HitBox();

	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& l);
	void Draw(sf::RenderWindow& window);
};

