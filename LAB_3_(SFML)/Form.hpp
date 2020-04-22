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
	// Position//
	Position _pos;
	// Size //
	Position _size;
	// Rounding? //
	bool _rounding;
	// Color //
	sf::Color _color;
	// State //
	State _state;
	// Render window //
	std::shared_ptr<sf::RenderWindow> _window;

public:
	// Ñonstructors //
	explicit Form() { _pos = { 0, 0 }, _rounding = false, _size._x = 0, _size._y = 0, _color = sf::Color(), _state = State::Inactive, _window = nullptr; }
	explicit Form(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, Position size = { 0, 0 }, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) { _pos = pos, _rounding = rounding, _size._x = size._x, _size._y = size._y, _color = color, _state = state, _window = window; }
	
	// Destructor //
	virtual ~Form() { _window = nullptr; }
	
	// Getters //
	virtual Position GetPosition() { return _pos; }
	virtual float GetWidth() { return _size._x; }
	virtual float GetHeight() { return _size._y; }
	virtual sf::Color GetColor() { return _color; }
	virtual State GetState() { return _state; }
	virtual std::shared_ptr<sf::RenderWindow> GetWindow() { return _window; }

	// Setters //
	virtual void SetPosition(Position& pos) { _pos._x = pos._x; _pos._y = pos._y; }
	virtual void SetWidth(float width) { _size._x = width; }
	virtual void SetHeight(float height) { _size._y = height; }
	virtual void SetRounding(bool rounding) { _rounding = rounding; }
	virtual void SetColor(sf::Color color) { _color = color; }
	virtual void SetState(State state) { _state = state; }
	virtual void SetWindow(std::shared_ptr<sf::RenderWindow> window) { _window = window; }

	// Methods //
	virtual void Draw() = 0;
	virtual Form* Clone() = 0;

	// Operators //
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
	SelectColor, SelectScale, Hide_Show, Clear,

	//////////////////////////////

	circ, rect, triang, unit
};

class Button final: public Form
{
	// Friends //
	friend class Panel;

private:
	// Token //
	Token _action;

public:
	// Ñonstructors //
	explicit Button() : Form(), _action{ Token::None } {}
	explicit Button(std::shared_ptr<sf::RenderWindow> window, const Token token = Token::None, const Position pos = { 0, 0 }, const Position size = { 0, 0 }, const sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, size, color, state, rounding), _action{ token } {}
	explicit Button(const Button& but) : Form(but._window, but._pos, but._size, but._color, but._state, but._rounding), _action{ but._action } {}

	// Destructor //
	~Button() {}

	// Getters //
	Token GetToken() { return _action; }

	// Setters //
	void SetToken(Token token) { _action = token; }

	// Methods //
	virtual void Draw() override;
	virtual Form* Clone() override { return new Button(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        TextBox
//----------------------------------------------------------------------------------------------------

class TextBox final : public Form
{
public:
	// Ñonstructor //
	explicit TextBox() : Form() {}
	explicit TextBox(std::shared_ptr<sf::RenderWindow> window, const Position pos = { 0, 0 }, const Position size = { 0, 0 }, const sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, size, color, state, rounding) {}
	explicit TextBox(const TextBox& box) : Form(box._window, box._pos, box._size, box._color, box._state, box._rounding) {}

	// Destructor //
	~TextBox() {}

	// Methods //
	virtual void Draw() override;
	virtual Form* Clone() override { return new TextBox(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        Panel
//----------------------------------------------------------------------------------------------------

class Panel final : public Form
{
	// Friends //
	friend class Interface;

private:
	// Shapes //
	std::vector<Form*> _elem;

public:
	// Ñonstructor //
	explicit Panel() : Form() {}
	explicit Panel(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, Position size = { 0, 0 }, sf::Color color = sf::Color(), State state = State::Inactive, bool rounding = false) : Form(window, pos, size, color, state, rounding) {}
	explicit Panel(const Panel& form) : Form(form._window, form._pos, form._size, form._color, form._state, form._rounding), _elem{ form._elem } {}

	// Destructor //
	~Panel() {}

	// Methods //
	bool OnPanel(Form& form);
	bool CheckOverlay(Form& form);
	void Add(Form& form);

	virtual void Draw() override;
	virtual Form* Clone() override { return new Panel(*this); }
};

#endif
