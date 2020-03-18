#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

//----------------------------------------------------------------------------------------------------
//                                        INCLUDE
//----------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "Position.hpp"
#include <Windows.h>

//----------------------------------------------------------------------------------------------------
//                                        SCREEN
//----------------------------------------------------------------------------------------------------

#define SC_WIDTH 1280
#define SC_HEIGHT 720

#define MSG_WIDTH SC_WIDTH/2
#define MSG_HEIGHT SC_HEIGHT/2

#define FULLSC sf::Style::Fullscreen
#define WINDOW sf::Style::Default
#define NONE sf::Style::None

//----------------------------------------------------------------------------------------------------
//                                        INTERFACE
//----------------------------------------------------------------------------------------------------

#define BACKGROUND_COLOR sf::Color(130, 130, 130)
#define PANEL_COLOR sf::Color(190, 190, 190)
#define BUTTOM_COLOR sf::Color(200, 200, 200)

#define SMALL_BUT sf::Vector2f(45, 45)
#define STANDARD_BUT sf::Vector2f(120, 45)
#define BIG_BUT sf::Vector2f(260, 45)

#endif