#pragma once

#ifndef DIALOG_H
#define DIALOG_H

#include "ShapeFactory.hpp"

class Dialog final
{
public:
	static std::string OpenFileDialog();
	static Shape* OpenFiguresDialog();
	static sf::Color OpenColorDialog();
	static Position OpenScaleDialog();
};

#endif
