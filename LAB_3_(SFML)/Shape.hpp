#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Interface.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shape
//----------------------------------------------------------------------------------------------------

class Shape
{
protected:
	Position _pos;
	float _angle;
	Position _scale;

	bool _visible = true;
	bool _outline = false;
	sf::Color _color;

	std::shared_ptr<sf::RenderWindow> _window;

	virtual void Update() = 0;
	virtual Position GetPoint(const int index) = 0;

public:
	Shape() { _pos = { 0, 0 }, _angle = 0, _color = sf::Color(), _scale = { 1, 1 }, _window = nullptr; }
	Shape(std::shared_ptr<sf::RenderWindow> window, const Position pos = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0, const Position scale = { 1, 1 }) { _pos = pos, _angle = angle, _color = color, _scale = scale, _window = window; }
	Shape(std::shared_ptr<sf::RenderWindow> window, const float x = 0, const float y = 0, const sf::Color color = sf::Color(), const float angle = 0, const float scale_x = 1, const float scale_y = 1) { _pos._x = x, _pos._y = y, _angle = angle, _color = color, _scale = Position(scale_x, scale_y), _window = window; }

	virtual ~Shape() { _window = nullptr; }

	virtual size_t GetPointCount() const = 0;
	virtual Position GetPosition() const { return _pos; }
	virtual float GetAngle() const { return _angle; }
	virtual Position GetScale() const { return _scale; }
	virtual sf::Color GetColor() const { return _color; }
	virtual std::shared_ptr<sf::RenderWindow> GetWindow() const { return _window; }
	virtual bool GetVisible() { return _visible; }

	virtual void SetPosition(Position& pos) { _pos._x = pos._x; _pos._y = pos._y; Update(); }
	virtual void SetSize(const Position size) = 0;
	virtual void SetOutlineThickness(bool what) { _outline = what; Update(); }
	virtual void SetAngle(float angle) { _angle = angle; Update(); }
	virtual void SetScale(float scale_x, float scale_y) { _scale = Position(scale_x, scale_y); Update(); }
	virtual void SetColor(sf::Color color) { _color = color; Update(); }
	virtual void SetWindow(std::shared_ptr<sf::RenderWindow> window) { _window = window; }
	virtual void SetVisible(bool what) { _visible = what; Update(); }

	virtual void Draw() = 0;
	virtual void Move(const float x, const float y) { _pos._x += x, _pos._y += y; Update(); };
	virtual void Rotate(const int angle) { _angle = (int)(_angle + angle + 360) % 360; Update(); }

	virtual bool OnArea(const float xa, const float ya) = 0;

	static bool Check—ollision(Shape* first, Shape* second);
};

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

class Circle final: public Shape
{
protected:
	float _radius;
	sf::CircleShape _shape;

	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	Circle() : Shape(), _radius{ 0 } { Update(); }
	Circle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _radius{ radius } { Update(); }
	Circle(std::shared_ptr<sf::RenderWindow> window, const float x = 0, const float y = 0, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, x, y, color, angle), _radius{ radius } { Update(); }

	virtual ~Circle() {}

	virtual size_t GetPointCount() const override { return 16; }
	float GetRadius() const { return _radius; }

	void SetSize(const Position size) override { _radius = size._x; Update(); }

	virtual void Draw() override;

	virtual bool OnArea(const float x, const float y) override;
};

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

class Rectangle final: public Shape
{
protected:
	float _width, _height;
	sf::RectangleShape _shape;

	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	Rectangle() : Shape(), _width{ 0 }, _height{ 0 } { Update(); }
	Rectangle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, Position size = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _width{ size._x }, _height{ size._y } { Update(); }
	Rectangle(std::shared_ptr<sf::RenderWindow> window, const float x = 0, const float y = 0, const float width = 0, const float height = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, x, y, color, angle), _width{ width }, _height{ height } { Update(); }

	virtual ~Rectangle() {}

	virtual size_t GetPointCount() const override { return 4; }

	void SetSize(const Position size) override { _width = size._x, _height = size._y; Update(); }

	virtual void Draw() override;

	virtual bool OnArea(const float x, const float y) override;
};

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

class Triangle final: public Shape
{
protected:
	float _radius;
	sf::CircleShape _shape;

	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	Triangle() : Shape(), _radius{ 0 } { Update(); }
	Triangle(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _radius{ radius } { Update(); }
	Triangle(std::shared_ptr<sf::RenderWindow> window, const float x = 0, const float y = 0, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, x, y, color, angle), _radius{ radius } { Update(); }

	~Triangle() {}

	virtual size_t GetPointCount() const override { return 3; }

	void SetSize(const Position size) override { _radius = size._x; Update(); }

	virtual void Draw() override;

	virtual bool OnArea(const float x, const float y) override;
};

//----------------------------------------------------------------------------------------------------
//                                        Star
//----------------------------------------------------------------------------------------------------

class Star final : public Shape
{
private:
	float _radius;
	sf::CircleShape _shape;

	virtual void Update() override;
	virtual Position GetPoint(const int index) override;

public:
	Star() : Shape(), _radius{ 0 } { Update(); }
	Star(std::shared_ptr<sf::RenderWindow> window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _radius{ radius } { Update(); }
	Star(std::shared_ptr<sf::RenderWindow> window, const float x = 0, const float y = 0, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, x, y, color, angle), _radius{ radius } { Update(); }

	~Star() {}

	virtual size_t GetPointCount() const override { return 5; }

	void SetSize(const Position size) override { _radius = size._x; Update(); }

	virtual void Draw() override;

	virtual bool OnArea(const float x, const float y) override;
};

//----------------------------------------------------------------------------------------------------
//                                        UnitShape
//----------------------------------------------------------------------------------------------------

class UnitShape final : public Shape
{
protected:
	std::vector<Shape*> _elem;

	virtual void Update() override {};
	virtual Position GetPoint(const int index) override { return Position(); };

public:
	UnitShape() {}
	UnitShape(std::shared_ptr<sf::RenderWindow> window, std::vector<Shape*> shapes, Position pos = { 0, 0 }, const float angle = 0, const Position scale = { 1, 1 }) : Shape(window, pos, sf::Color(), angle, scale) { _elem = shapes; }

	virtual size_t GetPointCount() const;
	void SetSize(const Position size) override {}

	virtual void Draw() override;
	virtual void Move(const float x, const float y) override { _pos._x += x, _pos._y += y; for (auto shape : _elem) { shape->Move(x, y); } Update(); };
	virtual void Rotate(const int angle) override { _angle = (int)(_angle + angle + 360) % 360; for (auto shape : _elem) { shape->Rotate(angle); } Update(); }

	virtual bool OnArea(const float x, const float y) override;
};

#endif