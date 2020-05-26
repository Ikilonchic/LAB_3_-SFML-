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
	// Render window //
	std::shared_ptr<sf::RenderWindow> _window;
	// Background //
	sf::RectangleShape _background;
	// Panels //
	std::vector<Panel*> _form;
	// Focus? //
	Form* _focus;

public:
	// Constructors //
	explicit Interface() { _window = nullptr, _focus = nullptr; }

	// Destructors //
	virtual ~Interface() { _window = nullptr, _focus = nullptr; }

	// Getters //
	virtual std::shared_ptr<sf::RenderWindow> GetWindow() { return _window; }
	virtual Form* GetFocus() { return _focus; }

	// Setters //
	virtual void SetWindow(std::shared_ptr<sf::RenderWindow> window) { _window = window; }
	virtual void SetBackground(sf::RectangleShape& background) { _background = background; }

	// Methods //
	virtual void AddPanel(Panel& form);
	virtual bool CheckOverlay(Form& form);
	virtual Form* CheckFocused(Position& mouse);
	virtual Form* CheckFocused(float x, float y);
	
	virtual void DrawFocus(Form* focus);
	virtual void Draw();
};

#endif