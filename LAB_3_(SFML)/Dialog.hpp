#pragma once

#ifndef DIALOG_H
#define DIALOG_H

#include "InfoManager.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Dialog
//----------------------------------------------------------------------------------------------------

class Dialog final
{
public:
	// Methods //
	static std::string OpenFileDialog();
	static std::unique_ptr<Shape> OpenFiguresDialog(std::unique_ptr<Factory>& fac);
	static sf::Color OpenColorDialog();
	static Position OpenScaleDialog();
};

#endif
