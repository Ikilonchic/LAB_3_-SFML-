#pragma once

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shape factory
//----------------------------------------------------------------------------------------------------

class Factory
{
private:
	std::shared_ptr<sf::RenderWindow> _window;

public:
	Factory(std::shared_ptr<sf::RenderWindow> window) { _window = window; }
	~Factory() {}

	static Shape* MakeShape(Token token, std::shared_ptr<sf::RenderWindow> window, const Position pos = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0, const Position scale = { 1, 1 });
};

#endif