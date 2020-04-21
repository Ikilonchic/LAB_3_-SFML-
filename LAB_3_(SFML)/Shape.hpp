#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Interface.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shape
//----------------------------------------------------------------------------------------------------

class Shape
{
	// Friends //
	friend class InfoManager;
	friend class UnitShape;

protected:
	// Name //
	std::string _name;
	// Position //
	Position _pos = { 0, 0 };
	// Size //
	Position _size = { 0, 0 };
	// Angle //
	float _angle = 0;
	// Scale //
	Position _scale = { 0, 0 };
	// Move //
	Position _move = { 0, 0 };
	// Visible? //
	bool _visible = true;
	// Outline? //
	bool _outline = false;
	// Tail? //
	bool _tail = false;
	// Color //
	sf::Color _color = sf::Color();
	// Render window //
	std::shared_ptr<sf::RenderWindow> _window = nullptr;

	// Private methods //
	virtual void Update() = 0;
	virtual Position GetPoint(const int index) = 0;
	virtual void AutoMove();

public:
	// —onstructors //
	explicit Shape() {}
	explicit Shape(std::shared_ptr<sf::RenderWindow> window, const Position pos = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0, const Position scale = { 1, 1 }) { _pos = pos, _angle = angle, _color = color, _scale = scale, _window = window; }
	
	// Destructors //
	virtual ~Shape() { _window = nullptr; }

	// Getters //
	virtual std::string GetName() { return _name; }
	virtual size_t GetPointCount() const = 0;
	virtual Position GetPosition() const { return _pos; }
	virtual float GetAngle() const { return _angle; }
	virtual Position GetSize() const { return _size; }
	virtual Position GetScale() const { return _scale; }
	virtual sf::Color GetColor() const { return _color; }
	virtual std::shared_ptr<sf::RenderWindow> GetWindow() const { return _window; }
	virtual bool GetVisible() { return _visible; }
	virtual bool GetTail() { return _tail; }

	virtual Position GetMove() { return _move; }

	// Setters //
	virtual void SetPosition(Position& pos) { _pos._x = pos._x; _pos._y = pos._y; Update(); }
	virtual void SetSize(const Position size) = 0;
	virtual void SetOutlineThickness(bool what) { _outline = what; Update(); }
	virtual void SetAngle(float angle) { _angle = angle; Update(); }
	virtual void SetScale(Position scale) { _scale = scale; Update(); }
	virtual void SetColor(sf::Color color) { _color = color; Update(); }
	virtual void SetWindow(std::shared_ptr<sf::RenderWindow> window) { _window = window; }
	virtual void SetVisible(bool what) { _visible = what; Update(); }
	virtual void SetTail(bool what) { _tail = what; Update(); }

	virtual void SetMove(Position vector) { _move = vector; }

	// Methods //
	virtual void Draw() = 0;
	virtual void Move(const float x, const float y) { _pos._x += x, _pos._y += y; Update(); };
	virtual void Rotate(const int angle) { _angle = (int)(_angle + angle + 360) % 360; Update(); }
	virtual Shape* Clone() = 0;

	virtual SIDE OnArea(const float xa, const float ya);

	static bool Check—ollision(Shape* first, Shape* second);
};

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

class Circle final: public Shape
{
protected:
	// SFML shape //
	sf::CircleShape _shape;
	// Tail //
	std::vector<sf::CircleShape> _tail;
	
	// Private methods //
	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	// Constructors //
	explicit Circle() : Shape() { Update(); _name = "circ"; _size = { 0, 0 }; }
	explicit Circle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0, Position scale = { 1, 1 }) : Shape(window, pos, color, angle, scale) { _name = "circ"; _size._x = radius; Update(); }
	explicit Circle(const Circle& temp) : Shape(temp._window, temp._pos, temp._color, temp._angle, temp._scale) { _name = "circ"; _size._x = temp._size._x; Update(); }
	
	// Destructors //
	virtual ~Circle() {}

	// Getters //
	virtual size_t GetPointCount() const override { return 16; }

	// Setters //
	void SetSize(const Position size) override { _size._x = size._x; Update(); }
	
	// Methods //
	virtual void Draw() override;
	virtual Shape* Clone() override { return new Circle(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

class Rectangle final: public Shape
{
protected:
	// SFML shape //
	sf::RectangleShape _shape;
	// Tail //
	std::vector<sf::RectangleShape> _tail;
	 
	// Private methods //
	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	// Constructors //
	explicit Rectangle() : Shape() { Update(); _name = "rect"; _size = { 0, 0 }; }
	explicit Rectangle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, Position size = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0, Position scale = { 1, 1 }) : Shape(window, pos, color, angle, scale) { Update(); _name = "rect"; _size = { size._x, size._y }; }
	explicit Rectangle(const Rectangle& temp) : Shape(temp._window, temp._pos, temp._color, temp._angle, temp._scale) { _name = "rect"; _size = { temp._size._x, temp._size._y }; Update(); }

	// Destructors //
	virtual ~Rectangle() {}
	
	// Getters //
	virtual size_t GetPointCount() const override { return 4; }

	// Setters //
	void SetSize(const Position size) override { _size = {size._x, size._y}; Update(); }

	// Methods //
	virtual void Draw() override;
	virtual Shape* Clone() override { return new Rectangle(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

class Triangle final: public Shape
{
protected:
	// SFML shape //
	sf::CircleShape _shape;
	// Tail //
	std::vector<sf::CircleShape> _tail;

	// Private methods //
	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	// Constructors //
	explicit Triangle() : Shape() { Update(); _name = "tria"; _size = { 0, 0 }; }
	explicit Triangle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0, Position scale = { 1, 1 }) : Shape(window, pos, color, angle, scale) { Update(); _name = "tria"; _size = { radius, 0 }; }
	explicit Triangle(const Triangle& temp) : Shape(temp._window, temp._pos, temp._color, temp._angle, temp._scale) { _name = "tria"; _size._x = temp._size._x; Update(); }

	// Destructors //
	virtual ~Triangle() {}
	
	// Getters //
	virtual size_t GetPointCount() const override { return 3; }

	// Setters //
	void SetSize(const Position size) override { _size._x = size._x; Update(); }

	// Methods //
	virtual void Draw() override;
	virtual Shape* Clone() override { return new Triangle(*this); }
};

//----------------------------------------------------------------------------------------------------
//                                        UnitShape
//----------------------------------------------------------------------------------------------------

class UnitShape final : public Shape
{
protected:
	// SFML shapes //
	std::vector<Shape*> _elem;

	// Private methods //
	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	// Constructors //
	explicit UnitShape() { _name = "unit"; }
	explicit UnitShape(std::shared_ptr<sf::RenderWindow> window, std::vector<Shape*> shapes) : Shape(window, { 0, 0 }) { _elem = shapes; _name = "unit"; if (_elem.size() != 0) { Update(); } }
	explicit UnitShape(const UnitShape& temp) : Shape(temp._window, { 0, 0 }) { _elem = temp._elem; _name = "unit"; if (_elem.size() != 0) { Update(); } }

	// Getters //
	virtual size_t GetPointCount() const;
	virtual std::vector<Shape*> GetShapes() { return _elem; }

	// Setters //
	virtual void SetPosition(Position& pos) { _pos._x = pos._x; _pos._y = pos._y; for (auto shape : _elem) { shape->SetPosition(pos); } }
	virtual void SetSize(const Position size) override {};
	virtual void SetOutlineThickness(bool what) { _outline = what; for (auto shape : _elem) { shape->SetOutlineThickness(what); } }
	virtual void SetAngle(float angle) { _angle = angle; }
	virtual void SetScale(Position scale) { _scale = scale; for (auto shape : _elem) { shape->SetScale(scale); } }
	virtual void SetColor(sf::Color color) { _color = color; for (auto shape : _elem) { shape->SetColor(color); } }
	virtual void SetWindow(std::shared_ptr<sf::RenderWindow> window) { _window = window; for (auto shape : _elem) { shape->SetWindow(window); } }
	virtual void SetVisible(bool what) { _visible = what; for (auto shape : _elem) { shape->SetVisible(what); } }
	virtual void SetTail(bool what) { _tail = what; for (auto shape : _elem) { shape->SetTail(what); } }
	virtual void SetShapes(std::vector<Shape*> shapes) { _elem = shapes; if (_elem.size() != 0) { Update(); } }

	virtual void SetMove(Position vector) { _move = vector; for (auto shape : _elem) { shape->SetMove(vector); } }

	// Methods //
	virtual void Draw() override;
	virtual Shape* Clone() override { return new UnitShape(*this); }

	virtual void Move(const float x, const float y) override { _pos._x += x, _pos._y += y; for (auto shape : _elem) { shape->Move(x, y); } };
	virtual void Rotate(const int angle) override { _angle = (int)(_angle + angle + 360) % 360; for (auto shape : _elem) { shape->Rotate(angle); } }
};

#endif