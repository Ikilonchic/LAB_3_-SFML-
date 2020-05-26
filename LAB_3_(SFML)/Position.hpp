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

	// Methods //

	static bool AreCrossing(const Position A, const Position B, const Position C, const Position D) {
		double denominator;

		denominator = (D._y - C._y) * (A._x - B._x) - (D._x - C._x) * (A._y - B._y);

		if (denominator == 0) {
			if ((A._x * B._y - B._x * A._y) * (D._x - C._x) - (C._x * D._y - D._x * C._y) * (B._x - A._x) == 0 && (A._x * B._y - B._x * A._y) * (D._y - C._y) - (C._x * D._y - D._x * C._y) * (B._y - A._y) == 0) {
				return true;
			}
			else {
				return false;
			}
		} 
		else {
			double numerator_a = (D._x - B._x) * (D._y - C._y) - (D._x - C._x) * (D._y - B._y);
			double numerator_b = (A._x - B._x) * (D._y - B._y) - (D._x - B._x) * (A._y - B._y);

			double Ua = numerator_a / denominator;
			double Ub = numerator_b / denominator;

			return Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1 ? true : false;
		}
	}

	// Operators //
	friend bool operator==(const Position& pos1, const Position& pos2) {
		if (pos1._x == pos2._x && pos1._y == pos2._y) {
			return true;
		}
		return false;
	}

	friend bool operator!=(const Position& pos1, const Position& pos2) {
		if (pos1._x == pos2._x && pos1._y == pos2._y) {
			return false;
		}
		return true;
	}
};

#endif
