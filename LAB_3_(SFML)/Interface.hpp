#pragma once

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Form.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Interface
//----------------------------------------------------------------------------------------------------

class Interface
{
private:
	sf::RenderWindow* _window;
	std::vector<Panel*> _form;
	Form* _focus;

public:
	Interface() { _window = nullptr, _focus = nullptr; }

	virtual ~Interface() { _window = nullptr, _focus = nullptr; }

	virtual void AddPanel(Panel& form);
	virtual bool CheckOverlay(Form& form);
	virtual Form* CheckFocused(Position& mouse);
	virtual Form* CheckFocused(float x, float y);
	
	virtual void DrawFocus(Form* focus);
	virtual void Draw();
};

#endif