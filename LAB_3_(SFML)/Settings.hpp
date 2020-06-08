#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

//----------------------------------------------------------------------------------------------------
//                                        INCLUDE
//----------------------------------------------------------------------------------------------------

#define _USE_MATH_DEFINES

#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <SFML/Graphics.hpp>
//#include <Windows.h>
#include "Position.hpp"
#include "RoundedRectangleShape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        SCREEN
//----------------------------------------------------------------------------------------------------

#define TIMER 5.0f

#define SC_WIDTH 1280
#define SC_HEIGHT 720

#define MSG_WIDTH SC_WIDTH/2
#define MSG_HEIGHT SC_HEIGHT/2

#define DIFFERENCE float(SC_WIDTH) / 1280.0

#define FULLSC sf::Style::Fullscreen
#define WINDOW sf::Style::Default
#define NONE sf::Style::None

enum SIDE {
	NONE_SIDE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

//----------------------------------------------------------------------------------------------------
//                                        INTERFACE
//----------------------------------------------------------------------------------------------------

enum WINDOW_MODE {
	Standard, Standby, ShapeSelection
};

// Color //
#define BACKGROUND_COLOR sf::Color(130, 130, 130)
#define PANEL_COLOR sf::Color(190, 190, 190)
#define BUTTOM_COLOR sf::Color(200, 200, 200)
#define BLACK sf::Color(0, 0, 0)
#define WHITE sf::Color(255, 255, 255)

// Size //
#define SMALL_BUT Position(45 * DIFFERENCE, 45 * DIFFERENCE)
#define STANDARD_BUT Position(120 * DIFFERENCE, 45 * DIFFERENCE)
#define BIG_BUT Position(260 * DIFFERENCE, 45 * DIFFERENCE)

// Outline //
#define SMALL_OUTLINE 2 * DIFFERENCE
#define STANDARD_OUTLINE 2 * DIFFERENCE
#define BIG_OUTLINE 6 * DIFFERENCE

//----------------------------------------------------------------------------------------------------
//                                        MOVE
//----------------------------------------------------------------------------------------------------

#define MOVE_LEFT -2, 0
#define MOVE_RIGHT 2, 0
#define MOVE_UP 0, -2
#define MOVE_DOWN 0, 2

#define ROTATE_LEFT -2
#define ROTATE_RIGHT 2

#define TAIL_SIZE 30

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
{
	if (Derived* result = dynamic_cast<Derived*>(p.get())) {
		p.release();
		return std::unique_ptr<Derived, Del>(result,
			std::move(p.get_deleter()));
	}
	return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

#endif
