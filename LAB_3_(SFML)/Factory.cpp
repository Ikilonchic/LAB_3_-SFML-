#include "Factory.hpp"

std::unique_ptr<Shape> Factory::MakeShape(Token token, const Position pos, const sf::Color color, const float angle, const Position scale) {
	switch (token) {
		case Token::circ:
			return std::unique_ptr<Shape>(new Circle(_window, pos, 50, color, angle, scale));
		case Token::rect:
			return std::unique_ptr<Shape>(new Rectangle(_window, pos, {50, 50}, color, angle, scale));
		case Token::triang:
			return std::unique_ptr<Shape>(new Triangle(_window, pos, 50, color, angle, scale));
		case Token::unit:
			return std::unique_ptr<Shape>(new UnitShape(_window, std::vector<std::unique_ptr<Shape>>()));
	}
	return nullptr;
}
