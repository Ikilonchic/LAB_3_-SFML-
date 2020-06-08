#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Dialog.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shapes
//----------------------------------------------------------------------------------------------------

static int INDEX = 0;
static std::vector<std::unique_ptr<Shape>> FIGURES;

static std::vector<std::unique_ptr<Shape>> COLLIDING_FIGURES;
static sf::Color collision_color;

static int UNIT_INDEX = 0;
static std::vector<std::unique_ptr<Shape>> UNIT_FIGURES;

//----------------------------------------------------------------------------------------------------
//                                        Controller
//----------------------------------------------------------------------------------------------------

static std::shared_ptr<sf::RenderWindow> MAIN_WINDOW;
static WINDOW_MODE MODE;

class Controller
{
public:
	// Start app //
	static void InitApp();

private:
	// Private methods //
	static void SetInterface(std::shared_ptr<sf::RenderWindow> window, Interface& inter);
	static void DrawFigures(WINDOW_MODE mode);

	static void LongAction(Token token);
	static void ShortAction(std::unique_ptr<Factory>& fac, Token token);

	static void CheckCollision(int INDEX);
};

#endif