#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

//----------------------------------------------------------------------------------------------------
//                                        INCLUDE
//----------------------------------------------------------------------------------------------------

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
//#include <Windows.h>
#include "Position.hpp"

//----------------------------------------------------------------------------------------------------
//                                        SCREEN
//----------------------------------------------------------------------------------------------------

#define SC_WIDTH 1280
#define SC_HEIGHT 720

#define MSG_WIDTH SC_WIDTH/2
#define MSG_HEIGHT SC_HEIGHT/2

#define DIFFERENCE float(SC_WIDTH) / 1280.0

#define FULLSC sf::Style::Fullscreen
#define WINDOW sf::Style::Default
#define NONE sf::Style::None

//----------------------------------------------------------------------------------------------------
//                                        INTERFACE
//----------------------------------------------------------------------------------------------------

#define BACKGROUND_COLOR sf::Color(130, 130, 130)
#define PANEL_COLOR sf::Color(190, 190, 190)
#define BUTTOM_COLOR sf::Color(200, 200, 200)
#define BLACK sf::Color(0, 0, 0)
#define WHITE sf::Color(255, 255, 255)

#define SMALL_BUT Position(45 * DIFFERENCE, 45 * DIFFERENCE)
#define STANDARD_BUT Position(120 * DIFFERENCE, 45 * DIFFERENCE)
#define BIG_BUT Position(260 * DIFFERENCE, 45 * DIFFERENCE)

#define SMALL_OUTLINE 2 * DIFFERENCE
#define STANDARD_OUTLINE 2 * DIFFERENCE
#define BIG_OUTLINE 6 * DIFFERENCE
#endif
