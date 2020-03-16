#pragma once

#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
	float _x, _y;

public:
	Position() : _x{0}, _y{0} {}
	Position(float xa, float ya) : _x{xa}, _y{ya} {}
	Position(const Position& pos) : _x{pos._x}, _y{pos._y} {}

	virtual Position GetPosition() { return *this; }

	virtual const float GetX() { return _x; }
	virtual const float GetY() { return _y; }

	virtual void SetPosition(const float xa, const float ya) { _x = xa, _y = ya; }

	virtual void SetX(float xa) { _x = xa; }
	virtual void SetY(float ya) { _y = ya; }
};

#endif
