#include "Factory.hpp"

Shape* Factory::MakeShape(Token token, const Position pos, const sf::Color color, const float angle, const Position scale) {
	switch (token) {
		case Token::circ:
			return new Circle(_window, pos, 50, color, angle, scale);
		case Token::rect:
			return new Rectangle(_window, pos, {50, 50}, color, angle, scale);
		case Token::triang:
			return new Triangle(_window, pos, 50, color, angle, scale);
		case Token::unit:
			return new UnitShape(_window, std::vector<Shape*>());
	}
	return nullptr;
}
