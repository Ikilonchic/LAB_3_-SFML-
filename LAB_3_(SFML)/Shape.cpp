#include "Shape.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Shape
//----------------------------------------------------------------------------------------------------

void Shape::AutoMove() {
	if (!(_move == Position(0, 0))) {
		Move(_move._x, _move._y);

		SIDE check = OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT);

		if (!(check == SIDE::NONE_SIDE)) {
			Move(-_move._x, -_move._y);

			switch (check) {
				case SIDE::LEFT:
					_move._x = -_move._x;
					break;
				case SIDE::RIGHT:
					_move._x = -_move._x;
					break;
				case SIDE::TOP:
					_move._y = -_move._y;
					break;
				case SIDE::BOTTOM:
					_move._y = -_move._y;
					break;
			}
			SetMove(_move);
		}
	}
}

SIDE Shape::OnArea(const float xa, const float ya) {
	for (auto i = 0; i < GetPointCount(); i++) {
		if (GetPoint(i)._x <= 0) {
			return SIDE::LEFT;
		}
		else if (GetPoint(i)._x >= xa) {
			return SIDE::RIGHT;
		}
		else if (GetPoint(i)._y <= 0) {
			return SIDE::TOP;
		}
		else if (GetPoint(i)._y >= ya) {
			return SIDE::BOTTOM;
		}
	}
	return SIDE::NONE_SIDE;
}

bool Shape::CheckÑollision(Shape* first, Shape* second) {
	Position temp;

	if (first->GetPosition()._x - second->GetPosition()._x < 0) {
		temp._x = -1000;
	}
	else if (first->GetPosition()._x - second->GetPosition()._x > 0) {
		temp._x = 1000;
	}

	if (first->GetPosition()._y - second->GetPosition()._y < 0) {
		temp._y = -1000;
	}
	else if (first->GetPosition()._y - second->GetPosition()._y > 0) {
		temp._y = 1000;
	}

	for (size_t i = 0; i < first->GetPointCount(); i++) {
		for (size_t j = 0; j < second->GetPointCount(); j++) {
			if (Position::AreCrossing(temp, first->GetPoint(i), second->GetPoint(j), second->GetPoint((j + 1) % second->GetPointCount()))) {
				return true;
			}
		}
	}

	if (second->GetPosition()._x - first->GetPosition()._x < 0) {
		temp._x = -1000;
	}
	else if (second->GetPosition()._x - first->GetPosition()._x > 0) {
		temp._x = 1000;
	}

	if (second->GetPosition()._y - first->GetPosition()._y < 0) {
		temp._y = -1000;
	}
	else if (second->GetPosition()._y - first->GetPosition()._y > 0) {
		temp._y = 1000;
	}

	for (size_t i = 0; i < second->GetPointCount(); i++) {
		for (size_t j = 0; j < first->GetPointCount(); j++) {
			if (Position::AreCrossing(temp, second->GetPoint(i), first->GetPoint(j), first->GetPoint((j + 1) % first->GetPointCount()))) {
				return true;
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------------------
//                                        Circle
//----------------------------------------------------------------------------------------------------

void Circle::Update() {
	sf::CircleShape circ;

	_color.a = _visible ? 255 : 0;

	circ.setOutlineColor(BLACK);

	circ.setOutlineThickness(_outline ? SMALL_OUTLINE : 0);

	circ.setFillColor(_color);
	circ.setRadius(_size._x);
	circ.setOrigin(_size._x, _size._x);
	circ.setPosition(sf::Vector2f(_pos._x, _pos._y));

	sf::Vector2f scale = circ.getScale();

	circ.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = circ;
}

Position Circle::GetPoint(const int index) {
	if (index < 16) {
		sf::Vector2f vec = _shape.getPoint(index * _shape.getPointCount() / 16);

		Position pos(vec.x, vec.y);

		pos._x -= _size._x;
		pos._y -= _size._x;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Circle::Draw() {
	AutoMove();
	_window->draw(_shape);
}

//----------------------------------------------------------------------------------------------------
//                                        Rectangle
//----------------------------------------------------------------------------------------------------

void Rectangle::Update() {
	sf::RectangleShape rect;

	_color.a = _visible ? 255 : 0;

	rect.setOutlineColor(BLACK);

	rect.setOutlineThickness(_outline ? SMALL_OUTLINE : 0);

	rect.setFillColor(_color);
	rect.setSize(sf::Vector2f(_size._x, _size._y));
	rect.setOrigin(_size._x / 2, _size._y / 2);
	rect.setPosition(_pos._x, _pos._y);
	rect.rotate(_angle);

	sf::Vector2f scale = rect.getScale();

	rect.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = rect;
}

Position Rectangle::GetPoint(const int index) {
	if (index < GetPointCount()) {
		sf::Vector2f vec = _shape.getPoint(index);

		Position pos(vec.x, vec.y);

		pos._x -= _size._x / 2;
		pos._y -= _size._y / 2;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Rectangle::Draw() {
	AutoMove();
	_window->draw(_shape);
}

//----------------------------------------------------------------------------------------------------
//                                        Triangle
//----------------------------------------------------------------------------------------------------

void Triangle::Update() {
	sf::CircleShape triangle(_size._x, 3);

	_color.a = _visible ? 255 : 0;

	triangle.setOutlineColor(BLACK);

	triangle.setOutlineThickness(_outline ? SMALL_OUTLINE : 0);

	triangle.setFillColor(_color);
	triangle.setPosition(_pos._x, _pos._y);
	triangle.setOrigin(_size._x, _size._x);
	triangle.rotate(_angle);

	sf::Vector2f scale = triangle.getScale();

	triangle.scale(scale.x * _scale._x, scale.y * _scale._y);

	_shape = triangle;
}

Position Triangle::GetPoint(const int index) {
	if (index < GetPointCount()) {
		sf::Vector2f vec = _shape.getPoint(index);

		Position pos(vec.x, vec.y);

		pos._x -= _size._x;
		pos._y -= _size._x;

		pos._x *= _scale._x;
		pos._y *= _scale._y;

		float xa = pos._x, ya = pos._y;

		pos._x = xa * std::cos(_angle * M_PI / 180.0) - ya * std::sin(_angle * M_PI / 180.0);
		pos._y = xa * std::sin(_angle * M_PI / 180.0) + ya * std::cos(_angle * M_PI / 180.0);

		pos._x += _pos._x;
		pos._y += _pos._y;

		return pos;
	}

	return Position();
}

void Triangle::Draw() {
	AutoMove();
	_window->draw(_shape);
}

//----------------------------------------------------------------------------------------------------
//                                        UnitShape
//----------------------------------------------------------------------------------------------------

void UnitShape::Update() {
	_pos = { 0, 0 };

	_color = sf::Color();

	// Shrink to fit //
	std::vector<Shape*> temp;

	for (auto shape : _elem) {
		if (shape->_visible) {
			temp.push_back(shape->Clone());
		}
	}

	_elem = temp;

	// New parameters //
	for (auto shape : _elem) {
		_pos._x += shape->_pos._x;
		_pos._y += shape->_pos._y;

		_color.r += shape->_color.r;
		_color.g += shape->_color.g;
		_color.b += shape->_color.b;
	}

	_pos._x /= _elem.size();
	_pos._y /= _elem.size();

	_color.r /= _elem.size();
	_color.g /= _elem.size();
	_color.b /= _elem.size();

	for (auto shape : _elem) {
		shape->_window = _window;

		shape->_pos = _pos;
		shape->_color = _color;

		shape->Update();
	}
}

Position UnitShape::GetPoint(const int index) {
	int elem_index, point_index, count_point = 0;

	for (elem_index = 0; elem_index < _elem.size(); elem_index++) {
		
		if (count_point == 0) {
			if (index < _elem[elem_index]->GetPointCount()) {
				return _elem[elem_index]->GetPoint(index);
			}
		}
		else {
			if (index % count_point < _elem[elem_index]->GetPointCount()) {
				return _elem[elem_index]->GetPoint(index % count_point);
			}
		}


		count_point += _elem[elem_index]->GetPointCount();
	}

	return Position();
}

size_t UnitShape::GetPointCount() const {
	size_t count = 0;

	for (auto shape : _elem) {
		count += shape->GetPointCount();
	}

	return count;
}

void UnitShape::Draw() {
	AutoMove();

	// Restoring position on the first element //
	Position temp = _elem[0]->_pos;

	for (auto shape : _elem) {
		shape->SetPosition(temp);
		shape->Draw();
	}
}
