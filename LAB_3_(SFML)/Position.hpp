#pragma once

#ifndef POSITION_H
#define POSITION_H

//----------------------------------------------------------------------------------------------------
//                                        Position
//----------------------------------------------------------------------------------------------------

class Position
{
public:
	float _x, _y;

	Position() : _x{0}, _y{0} {}
	Position(float xa, float ya) : _x{xa}, _y{ya} {}
	Position(const Position& pos) : _x{pos._x}, _y{pos._y} {}

	virtual Position GetPosition() { return *this; }

	virtual void SetPosition(const float xa, const float ya) { _x = xa, _y = ya; }
};

#endif
