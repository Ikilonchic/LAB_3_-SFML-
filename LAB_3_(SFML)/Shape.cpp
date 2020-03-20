#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

void Circle::Update()
{
	sf::CircleShape circ;

	if (_visible)
	{
		_color.a = 255;
	}
	else
	{
		_color.a = 0;
	}

	circ.setOutlineColor(BLACK);

	if (_outline)
	{
		circ.setOutlineThickness(SMALL_OUTLINE);
	}
	else
	{
		circ.setOutlineThickness(0);
	}

	circ.setFillColor(_color);
	circ.setRadius(_radius);
	circ.setOrigin(_radius, _radius);
	circ.setPosition(sf::Vector2f(_pos._x, _pos._y));

	sf::Vector2f scale = circ.getScale();

	circ.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = circ;
}

sf::Vector2f Circle::GetPoint(const int index)
{
	if (index < 8)
	{
		sf::Vector2f pos = _shape.getPoint(index * (_shape.getPointCount() / 8));
		pos.x += _pos._x;
		pos.y += _pos._y;

		return pos;
	}

	return sf::Vector2f();
}

void Circle::Draw()
{
	_window->draw(_shape);
}

bool Circle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < 8; i += 2)
	{
		if (GetPoint(i).x > 0 && GetPoint(i).y > 0 && GetPoint(i).x < x && GetPoint(i).y < y)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

void Rectangle::Update()
{
	sf::RectangleShape rect;

	if (_visible)
	{
		_color.a = 255;
	}
	else
	{
		_color.a = 0;
	}

	rect.setOutlineColor(BLACK);

	if (_outline)
	{
		rect.setOutlineThickness(SMALL_OUTLINE);
	}
	else
	{
		rect.setOutlineThickness(0);
	}

	rect.setFillColor(_color);
	rect.setSize(sf::Vector2f(_width, _height));
	rect.setOrigin(_width / 2, _height / 2);
	rect.setPosition(_pos._x, _pos._y);
	rect.rotate(_angle);

	sf::Vector2f scale = rect.getScale();

	rect.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = rect;
}

sf::Vector2f Rectangle::GetPoint(const int index)
{
	size_t count = _shape.getPointCount();

	if (index < count)
	{
		sf::Vector2f pos = _shape.getPoint(index);

		pos.x -= _width / 2;
		pos.y -= _height / 2;

		pos.x += _pos._x;
		pos.y += _pos._y;

		return pos;
	}

	return sf::Vector2f();
}

void Rectangle::Draw()
{
	_window->draw(_shape);
}

bool Rectangle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < _shape.getPointCount(); i++)
	{
		if (GetPoint(i).x > 0 && GetPoint(i).y > 0 && GetPoint(i).x < x && GetPoint(i).y < y)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

void Triangle::Update()
{
	sf::CircleShape triangle(_radius, 3);

	if (_visible)
	{
		_color.a = 255;
	}
	else
	{
		_color.a = 0;
	}

	triangle.setOutlineColor(BLACK);

	if (_outline)
	{
		triangle.setOutlineThickness(SMALL_OUTLINE);
	}
	else
	{
		triangle.setOutlineThickness(0);
	}

	triangle.setFillColor(_color);
	triangle.setPosition(_pos._x, _pos._y);
	triangle.setOrigin(_radius - 1, _radius - 1);
	triangle.rotate(_angle);

	sf::Vector2f scale = triangle.getScale();

	triangle.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = triangle;
}

sf::Vector2f Triangle::GetPoint(const int index)
{
	size_t count = _shape.getPointCount();

	if (index < count)
	{
		sf::Vector2f pos = _shape.getPoint(index);

		pos.x -= _radius;
		pos.y -= _radius;

		pos.x *= _scale._x;
		pos.y *= _scale._y;

		float xa = -pos.x, ya = -pos.y;

		pos.x = xa * cos(_angle) - (ya * sin(_angle));
		pos.y = (xa * sin(_angle)) + ya * cos(_angle);

		pos.x = -pos.x;
		pos.y = -pos.y;

		pos.x += _pos._x;
		pos.y += _pos._y;

		std::cout << _angle << std::endl;

		return pos;
	}

	return sf::Vector2f();
}

void Triangle::Draw()
{
	_window->draw(_shape);
}

bool Triangle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < _shape.getPointCount(); i++)
	{
		if (GetPoint(i).x > 0 && GetPoint(i).y > 0 && GetPoint(i).x < x && GetPoint(i).y < y)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}
