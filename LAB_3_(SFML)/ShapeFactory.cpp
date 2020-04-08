#include "ShapeFactory.hpp"

Shape* Factory::MakeShape(Token token, std::shared_ptr<sf::RenderWindow> window, const Position pos, const sf::Color color, const float angle, const Position scale)
{
	switch (token)
	{
	case Token::circ:
	{
		return new Circle(window, pos, 100, color, angle);
	}
	case Token::rect:
	{
		return new Rectangle(window, pos, {100, 100}, color, angle);
	}
	case Token::triang:
	{
		return new Triangle(window, pos, 100, color, angle);
	}
	case Token::unit:
	{
		return new UnitShape(window, std::vector<Shape*>(), pos, angle, scale);
	}
	}

	return nullptr;
}
