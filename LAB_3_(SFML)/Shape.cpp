#include "Shape.hpp"

std::vector<Position> Rectangle::GetPoints()
{


	return std::vector<Position>();
}

void Rectangle::Draw()
{
	sf::RectangleShape rect;

	rect.setFillColor(_color);
	rect.setSize(sf::Vector2f(_width, _height));
	rect.setPosition(_pos.GetX(), _pos.GetY());
	rect.rotate(_angle);

	_window->draw(rect);
}

void Triangle::Draw()
{
	sf::CircleShape triangle(80, 3);

	triangle.setFillColor(sf::Color(133, 56, 134));
	triangle.setPosition(400, 400);
	triangle.rotate(_angle);

	_window->draw(triangle);
}

void Circle::Draw()
{

}
