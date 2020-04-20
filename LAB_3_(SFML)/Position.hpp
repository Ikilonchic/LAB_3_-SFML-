#pragma once

#ifndef POSITION_H
#define POSITION_H

//----------------------------------------------------------------------------------------------------
//                                        Position
//----------------------------------------------------------------------------------------------------

class Position
{
public:
	// Coordinates //
	float _x, _y;

	// Constructors //
	Position() : _x{0}, _y{0} {}
	Position(float xa, float ya) : _x{xa}, _y{ya} {}
	Position(const Position& pos) : _x{pos._x}, _y{pos._y} {}

	// Getters //
	virtual Position GetPosition() { return *this; }

	// Setters //
	virtual void SetPosition(const float xa, const float ya) { _x = xa, _y = ya; }

	// Operators //
	friend bool operator==(const Position& pos1, const Position& pos2)
	{
		if (pos1._x == pos2._x && pos1._y == pos2._y) {
			return true;
		}

		return false;
	}

	friend bool operator!=(const Position& pos1, const Position& pos2)
	{
		if (pos1._x == pos2._x && pos1._y == pos2._y) {
			return false;
		}

		return true;
	}
};

#endif
