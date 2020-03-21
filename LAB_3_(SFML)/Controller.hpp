#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shapes
//----------------------------------------------------------------------------------------------------

static int INDEX = 0;
static std::vector<Shape*> FIGURES;

//----------------------------------------------------------------------------------------------------
//                                        Controller
//----------------------------------------------------------------------------------------------------

class Controller
{
public:
	static void InitApp();
	static void Instruction(sf::RenderWindow* window);

private:
	static void SetInterface(sf::RenderWindow* window, Interface& inter);

	static void LongAction(sf::RenderWindow* window, Form* action);
	static void ShortAction(sf::RenderWindow* window, Form* action);

	static std::string OpenFileDialog();
	static Shape* OpenFiguresDialog();
	static sf::Color OpenColorDialog();
	static Position OpenScaleDialog();

	static bool CheckCollision(int INDEX);
};

#endif