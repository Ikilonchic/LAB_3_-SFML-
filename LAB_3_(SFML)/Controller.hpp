#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Interface.hpp"
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

	static void Action(Form* action);

	static std::string OpenFileDialog();
	static Shape* OpenFiguresDialog();
	static sf::Color OpenColorDialog();
	static Position OpenScaleDialog();
};

#endif