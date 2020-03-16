#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Interface.hpp"
#include "Shape.hpp"

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
};

#endif