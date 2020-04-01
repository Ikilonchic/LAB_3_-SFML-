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

Position Circle::GetPoint(const int index)
{
	if (index < 16)
	{
		sf::Vector2f vec = _shape.getPoint(index * _shape.getPointCount() / 16);

		Position pos(vec.x, vec.y);

		pos._x -= _radius;
		pos._y -= _radius;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Circle::Draw()
{
	_window->draw(_shape);
}

bool Circle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < 16; i += 2)
	{
		if (!(GetPoint(i)._x > 0 && GetPoint(i)._y > 0 && GetPoint(i)._x < x && GetPoint(i)._y < y))
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

Position Rectangle::GetPoint(const int index)
{
	size_t count = _shape.getPointCount();

	if (index < count)
	{
		sf::Vector2f vec = _shape.getPoint(index);

		Position pos(vec.x, vec.y);

		pos._x -= _width / 2;
		pos._y -= _height / 2;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Rectangle::Draw()
{
	_window->draw(_shape);
}

bool Rectangle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < _shape.getPointCount(); i++)
	{
		if (!(GetPoint(i)._x > 0 && GetPoint(i)._y > 0 && GetPoint(i)._x < x && GetPoint(i)._y < y))
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

Position Triangle::GetPoint(const int index)
{
	size_t count = _shape.getPointCount();

	if (index < count)
	{
		sf::Vector2f vec = _shape.getPoint(index);

		Position pos(vec.x, vec.y);

		pos._x -= _radius;
		pos._y -= _radius;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Triangle::Draw()
{
	_window->draw(_shape);
}

bool Triangle::OnArea(const float x, const float y)
{
	for (auto i = 0; i < _shape.getPointCount(); i++)
	{
		if (!(GetPoint(i)._x > 0 && GetPoint(i)._y > 0 && GetPoint(i)._x < x && GetPoint(i)._y < y))
		{
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
//                                        Star
//----------------------------------------------------------------------------------------------------

void Star::Update()
{
	sf::CircleShape triangle(_radius, 5);

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

Position Star::GetPoint(const int index)
{
	return Position();
}

void Star::Draw()
{
	_window->draw(_shape);
}

bool Star::OnArea(const float x, const float y)
{
	for (auto i = 0; i < _shape.getPointCount(); i++)
	{
		if (!(GetPoint(i)._x > 0 && GetPoint(i)._y > 0 && GetPoint(i)._x < x && GetPoint(i)._y < y))
		{
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
//                                        Check collision
//----------------------------------------------------------------------------------------------------

bool AreCrossing(const Position A, const Position B, const Position C, const Position D)
{
	double denominator;

	denominator = (D._y - C._y) * (A._x - B._x) - (D._x - C._x) * (A._y - B._y);

	if (denominator == 0)
	{
		if ((A._x * B._y - B._x * A._y) * (D._x - C._x) - (C._x * D._y - D._x * C._y) * (B._x - A._x) == 0 && (A._x * B._y - B._x * A._y) * (D._y - C._y) - (C._x * D._y - D._x * C._y) * (B._y - A._y) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		double numerator_a = (D._x - B._x) * (D._y - C._y) - (D._x - C._x) * (D._y - B._y);
		double numerator_b = (A._x - B._x) * (D._y - B._y) - (D._x - B._x) * (A._y - B._y);

		double Ua = numerator_a / denominator;
		double Ub = numerator_b / denominator;

		return Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1 ? true : false;
	}
}

bool Shape::CheckÑollision(Shape* first, Shape* second)
{
	Position temp;

	if (first->GetPosition()._x - second->GetPosition()._x < 0)
	{
		temp._x = -1000;
	}
	else if (first->GetPosition()._x - second->GetPosition()._x > 0)
	{
		temp._x = 1000;
	}

	if (first->GetPosition()._y - second->GetPosition()._y < 0)
	{
		temp._y = -1000;
	}
	else if (first->GetPosition()._y - second->GetPosition()._y > 0)
	{
		temp._y = 1000;
	}

	for (size_t i = 0; i < first->GetPointCount(); i++)
	{
		for (size_t j = 0; j < second->GetPointCount(); j++)
		{
			if (AreCrossing(temp, first->GetPoint(i), second->GetPoint(j), second->GetPoint((j + 1) % second->GetPointCount())))
			{
				return true;
			}
		}
	}

	if (second->GetPosition()._x - first->GetPosition()._x < 0)
	{
		temp._x = -1000;
	}
	else if (second->GetPosition()._x - first->GetPosition()._x > 0)
	{
		temp._x = 1000;
	}

	if (second->GetPosition()._y - first->GetPosition()._y < 0)
	{
		temp._y = -1000;
	}
	else if (second->GetPosition()._y - first->GetPosition()._y > 0)
	{
		temp._y = 1000;
	}

	for (size_t i = 0; i < second->GetPointCount(); i++)
	{
		for (size_t j = 0; j < first->GetPointCount(); j++)
		{
			if (AreCrossing(temp, second->GetPoint(i), first->GetPoint(j), first->GetPoint((j + 1) % first->GetPointCount())))
			{
				return true;
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------------------
//                                        UnitShape
//----------------------------------------------------------------------------------------------------

size_t UnitShape::GetPointCount() const
{
	size_t count = 0;

	for (auto shape : _elem)
	{
		count += shape->GetPointCount();
	}

	return count;
}

void UnitShape::Draw()
{
	for (auto shape : _elem)
	{
		shape->Draw();
	}
}

bool UnitShape::OnArea(const float x, const float y)
{
	for (auto shape : _elem)
	{
		if (!(shape->OnArea(x, y)))
		{
			return false;
		}
	}

	return true;
}
