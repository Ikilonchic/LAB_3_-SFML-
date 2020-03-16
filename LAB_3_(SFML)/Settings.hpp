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

//----------------------------------------------------------------------------------------------------
//                                        SCREEN
//----------------------------------------------------------------------------------------------------

#define SC_WIDTH 1280
#define SC_HEIGHT 720

#define FULLSC sf::Style::Fullscreen
#define WINDOW sf::Style::Default

//----------------------------------------------------------------------------------------------------
//                                        INTERFACE
//----------------------------------------------------------------------------------------------------

#define MAIN_COLOR sf::Color(155, 155, 155)
#define BUTTOM_COLOR sf::Color(100, 100, 100)
#define BACKGROUND_COLOR sf::Color(200, 200, 200)

#endif