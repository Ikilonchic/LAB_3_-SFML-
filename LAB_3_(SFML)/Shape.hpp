#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Position.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

//----------------------------------------------------------------------------------------------------
//                                        Shape
//----------------------------------------------------------------------------------------------------

class Shape
{
protected:
	Position _pos;
	float _angle;
	Position _scale;

	sf::Color _color;

	sf::RenderWindow* _window;

	virtual std::vector<Position> GetPoints() = 0;

public:
	Shape() { _pos = { 0, 0 }, _angle = 0, _color = sf::Color(), _scale = { 1, 1 }, _window = nullptr; }
	Shape(sf::RenderWindow* window, Position pos = { 0, 0 }, const sf::Color color = sf::Color(), const float angle = 0, const Position scale = { 1, 1 }) { _pos = pos, _angle = angle, _color = color, _scale = scale, _window = window; }
	Shape(sf::RenderWindow* window, const float x = 0, const float y = 0, const sf::Color color = sf::Color(), const float angle = 0, const float scale_x = 1, const float scale_y = 1) { _pos.SetX(x), _pos.SetY(y), _angle = angle, _color = color, _scale = Position(scale_x, scale_y), _window = window; }

	virtual ~Shape() { _window = nullptr; }

	virtual Position GetPosition() const { return _pos; }
	virtual float GetAngle() const { return _angle; }
	virtual Position GetScale() const { return _scale; }
	virtual sf::Color GetColor() const { return _color; }
	virtual sf::RenderWindow* GetWindow() const { return _window; }

	virtual void SetPosition(Position& pos) { _pos.SetX(pos.GetX()); _pos.SetY(pos.GetY()); }
	virtual void SetAngle(float angle) { _angle = angle; }
	virtual void SetScale(float scale_x, float scale_y) { _scale = Position(scale_x, scale_y); }
	virtual void SetColor(sf::Color color) { _color = color; }
	virtual void SetWindow(sf::RenderWindow* window) { _window = window; }

	virtual void Draw() = 0;
	virtual void Move(const float x, const float y) { _pos.SetX(_pos.GetX() + x), _pos.SetY(_pos.GetY() + y); };
	virtual void Rotate(const int angle) { _angle = (int)(_angle + angle) % 360; }
};

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

class Circle final: public Shape
{
protected:
	float _radius;

	virtual std::vector<Position> GetPoints() override {};

public:
	Circle() : Shape(), _radius{ 0 } {}
	Circle(sf::RenderWindow* window, Position pos = { 0, 0 }, const float radius = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _radius{ radius } {}

	virtual ~Circle() {}

	float GetRadius() const { return _radius; }

	void SetRadius(float radius) { _radius = radius; }

	virtual void Draw() override;
};

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

class Rectangle final: public Shape
{
protected:
	float _width, _height;
	static const int _amount = 4;

	std::vector<Position> GetPoints();

public:
	Rectangle() : Shape(), _width{ 0 }, _height{ 0 } {}
	Rectangle(sf::RenderWindow* window, Position pos = { 0, 0 }, const float width = 0, const float height = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, pos, color, angle), _width{ width }, _height{ height } {}
	Rectangle(sf::RenderWindow* window, const float x = 0, const float y = 0, const float width = 0, const float height = 0, const sf::Color color = sf::Color(), const float angle = 0) : Shape(window, x, y, color, angle), _width{ width }, _height{ height } {}

	virtual ~Rectangle() {}

	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }

	void SetWidth(float width) { _width = width; }
	void SetHeight(float height) { _height = height; }

	virtual void Draw() override;
};

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

class Triangle : public Shape
{
protected:
	static const int _amount = 3;

	virtual std::vector<Position> GetPoints() override;

public:
	Triangle() : Shape() {}
	Triangle(sf::RenderWindow* window) { _window = window; }

	virtual void Draw() override;
};

#endif