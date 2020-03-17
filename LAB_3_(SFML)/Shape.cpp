#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

void Circle::Draw()
{

}

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

std::vector<Position> Rectangle::GetPoints()
{


	return std::vector<Position>();
}

void Rectangle::Draw()
{
	sf::RectangleShape rect;

	rect.setFillColor(_color);
	rect.setSize(sf::Vector2f(_width, _height));
	rect.setOrigin(_width / 2, _height / 2);
	rect.setPosition(_pos._x, _pos._y);
	rect.rotate(_angle);

	sf::Vector2f scale = rect.getScale();

	rect.scale(scale.x * _scale._x, scale.y * _scale._y);

	/*std::vector<Position> points = GetPoints();

	sf::ConvexShape rect;

	rect.setPointCount(_amount);
	rect.setFillColor(_color);

	for (auto i = 0; i < _amount; i++)
	{
		rect.setPoint(i, sf::Vector2f(points[i].GetX(), points[i].GetY()));
	}

	rect.setPosition(_pos.GetX(), _pos.GetY());
	*/

	_window->draw(rect);
}

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

std::vector<Position> Triangle::GetPoints()
{
	return std::vector<Position>();
}

void Triangle::Draw()
{
	sf::CircleShape triangle(80, 3);

	triangle.setFillColor(sf::Color(133, 56, 134));
	triangle.setPosition(400, 400);
	triangle.rotate(_angle);

	_window->draw(triangle);
}
