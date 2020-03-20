#pragma once

#ifndef FORM_H
#define FORM_H

#include "Settings.hpp"
#include "RoundedRectangleShape.hpp"

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
	Position _size;

	bool _rounding;

	sf::Color _color;

	State _state;

	sf::RenderWindow* _window;

public:
	Form() { _pos = { 0, 0 }, _rounding = false, _size._x = 0, _size._y = 0, _color = sf::Color(), _state = State::Inactive, _window = nullptr; }
	Form(sf::RenderWindow* window, Position pos = { 0, 0 }, Position size = { 0, 0 }, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) { _pos = pos, _rounding = rounding, _size._x = size._x, _size._y = size._y, _color = color, _state = state, _window = window; }
	Form(sf::RenderWindow* window, float x = 0, float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) { _pos = {x, y}, _rounding = rounding, _color = color, _size._x = width, _size._y = height, _state = state, _window = window; }

	virtual ~Form() { _window = nullptr; }

	virtual Position GetPosition() { return _pos; }
	virtual float GetWidth() { return _size._x; }
	virtual float GetHeight() { return _size._y; }
	virtual sf::Color GetColor() { return _color; }
	virtual State GetState() { return _state; }
	virtual sf::RenderWindow* GetWindow() { return _window; }

	virtual void SetPosition(Position& pos) { _pos._x = pos._x; _pos._y = pos._y; }
	virtual void SetWidth(float width) { _size._x = width; }
	virtual void SetHeight(float height) { _size._y = height; }
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

enum Token
{
	None,
	OK, Cancel,
	Left, Right, Up, Down,
	RotateLeft, RotateRight,
	Trail,
	ReadFromFile, SaveToFile,
	Add, Delete,
	Next, Prev,
	SelectColor, SelectScale, Hide_Show
};

class Button final: public Form
{
	friend class Panel;

private:
	Token _action;

	sf::Sprite _image;

public:
	Button() : Form(), _action{ Token::None } {}
	Button(sf::RenderWindow* window, const Token token = Token::None, float const x = 0, float const y = 0, const float width = 0, const float height = 0, const sf::Color color = sf::Color(), sf::Sprite image = sf::Sprite(), State state = State::Inactive, bool rounding = false) : Form(window, x, y, width, height, color, state, rounding), _action{ token } { _image = image; }
	Button(sf::RenderWindow* window, const Token token = Token::None, const Position pos = { 0, 0 }, const Position size = { 0, 0 }, const sf::Color color = sf::Color(), sf::Sprite image = sf::Sprite(), State state = State::Inactive, bool rounding = false) : Form(window, pos, size, color, state, rounding), _action{ token } { _image = image; }
	Button(const Button& but) : Form(but._window, but._pos, but._size, but._color, but._state, but._rounding), _action{ but._action } { _image = but._image; }

	~Button() {}

	Token GetToken() { return _action; }
	sf::Sprite GetImage() { return _image; }

	void SetToken(Token token) { _action = token; }

	virtual void Draw() override;
	virtual Form* Clone() override { return new Button(*this); }
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
	Panel(sf::RenderWindow* window, const float x = 0, const float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, x, y, width, height, color, state, rounding) {}
	Panel(sf::RenderWindow* window, Position pos = { 0, 0 }, Position size = { 0, 0 }, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, size, color, state, rounding) {}
	Panel(const Panel& form) : Form(form._window, form._pos, form._size, form._color, form._state, form._rounding), _elem{ form._elem } {}

	bool OnPanel(Form& form);
	bool CheckOverlay(Form& form);
	void Add(Form& form);

	virtual void Draw() override;
	virtual Form* Clone() override { return new Panel(*this); }
};

#endif
