#pragma once

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shape factory
//----------------------------------------------------------------------------------------------------

class Factory final
{
private:
	// Render window //
	std::shared_ptr<sf::RenderWindow> _window;

public:
	// Constructors //
	Factory(std::shared_ptr<sf::RenderWindow> window) { _window = window; }

	// Destructors //
	~Factory() {}
	
	// Methods //
	std::unique_ptr<Shape> MakeShape(Token token, const Position pos = { (SC_WIDTH * 3 / 8), (SC_HEIGHT / 2) }, const sf::Color color = sf::Color(64, 64, 64), const float angle = 0, const Position scale = { 1, 1 });
};

#endif