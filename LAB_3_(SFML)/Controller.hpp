#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Dialog.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shapes
//----------------------------------------------------------------------------------------------------

static int INDEX = 0;
static std::vector<Shape*> FIGURES;

static std::vector<Shape*> COLLIDING_FIGURES;
static sf::Color collision_color;

//----------------------------------------------------------------------------------------------------
//                                        Controller
//----------------------------------------------------------------------------------------------------

class Controller
{
public:
	static void InitApp();
	static void Instruction(std::shared_ptr<sf::RenderWindow> window);

private:
	static void SetInterface(std::shared_ptr<sf::RenderWindow> window, Interface& inter);
	static void DrawFigures();

	static void LongAction(std::shared_ptr<sf::RenderWindow> window, Form* action);
	static void ShortAction(std::shared_ptr<sf::RenderWindow> window, Form* action);

	static void CheckCollision(int INDEX);
};

#endif