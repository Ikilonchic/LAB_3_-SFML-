#pragma once

#ifndef FORM_H
#define FORM_H

#include "Settings.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Form
//----------------------------------------------------------------------------------------------------

enum State
{
	Inactive = 0,
	Focused,
	Active
};

class Form
{
protected:
	Position _pos;
	float _width, _height;

	bool _rounding;

	sf::Color _color;

	State _state;

	sf::RenderWindow* _window;

public:
	Form() { _pos = { 0, 0 }, _rounding = false, _width = 0, _height = 0, _color = sf::Color(), _state = State::Inactive, _window = nullptr; }
	Form(sf::RenderWindow* window, Position pos = { 0, 0 }, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) { _pos = pos, _rounding = rounding, _width = width, _height = height, _color = color, _state = state, _window = window; }
	Form(sf::RenderWindow* window, float x = 0, float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) { _pos = {x, y}, _rounding = rounding, _color = color, _width = width, _height = height, _state = state, _window = window; }

	virtual ~Form() { _window = nullptr; }

	virtual Position GetPosition() { return _pos; }
	virtual float GetWidth() { return _width; }
	virtual float GetHeight() { return _height; }
	virtual sf::Color GetColor() { return _color; }
	virtual State GetState() { return _state; }
	virtual sf::RenderWindow* GetWindow() { return _window; }

	virtual void SetPosition(Position& pos) { _pos.SetX(pos.GetX()); _pos.SetY(pos.GetY()); }
	virtual void SetWidth(float width) { _width = width; }
	virtual void SetHeight(float height) { _height = height; }
	virtual void SetRounding(bool rounding) { _rounding = rounding; }
	virtual void SetColor(sf::Color color) { _color = color; }
	virtual void SetState(State state) { _state = state; }
	virtual void SetWindow(sf::RenderWindow* window) { _window = window; }

	virtual void Draw() = 0;
	virtual Form* Clone() = 0;

	friend bool operator ==(Form& a, Form& b);
	friend bool operator ==(Form& a, Position& b);
};

//----------------------------------------------------------------------------------------------------
//                                        Buttom
//----------------------------------------------------------------------------------------------------

class Buttom final: public Form
{
	friend class Panel;

private:


public:
	Buttom() : Form() {}
	Buttom(sf::RenderWindow* window, Position pos = { 0, 0 }, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, width, height, color, state, rounding) {}
	Buttom(const Buttom& but) : Form(but._window, but._pos, but._width, but._height, but._color, but._state, but._rounding) {}

	virtual void Draw();
	virtual Form* Clone() { return new Buttom(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        Panel
//----------------------------------------------------------------------------------------------------

class Panel final : public Form
{
	friend class Interface;

private:
	std::vector<Form*> _elem;

public:
	Panel() : Form() {}
	Panel(sf::RenderWindow* window, Position pos = { 0, 0 }, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, width, height, color, state, rounding) {}
	Panel(const Panel& form) : Form(form._window, form._pos, form._width, form._height, form._color, form._state, form._rounding), _elem{ form._elem } {}

	bool OnPanel(Form& form);
	bool CheckOverlay(Form& form);
	void AddForm(Form& form);

	virtual void Draw();
	virtual Form* Clone() { return new Panel(*this); }
};

#endif