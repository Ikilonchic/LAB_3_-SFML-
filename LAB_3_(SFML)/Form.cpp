#include "Form.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Form
//----------------------------------------------------------------------------------------------------

bool operator==(Form& a, Form& b) {
	if (a._pos._x >= b._pos._x && a._pos._y >= b._pos._y && a._pos._x <= b._pos._x + b._size._x && a._pos._y <= b._pos._y + b._size._y) {
		return true;
	}
	else if (a._pos._x + a._size._x >= b._pos._x && a._pos._y + a._size._y >= b._pos._y && a._pos._x + a._size._x <= b._pos._x + b._size._x && a._pos._y + a._size._y <= b._pos._y + b._size._y) {
		return true;
	}
	else if (a._pos._x + a._size._x >= b._pos._x && a._pos._y >= b._pos._y && a._pos._x + a._size._x <= b._pos._x + b._size._x && a._pos._y <= b._pos._y + b._size._y) {
		return true;
	}
	else if (a._pos._x >= b._pos._x && a._pos._y + a._size._y >= b._pos._y && a._pos._x <= b._pos._x + b._size._x && a._pos._y + a._size._y <= b._pos._y + b._size._y) {
		return true;
	}

	if (b._pos._x >= a._pos._x && b._pos._y >= a._pos._y && b._pos._x <= a._pos._x + a._size._x && b._pos._y <= a._pos._y + a._size._y) {
		return true;
	}
	else if (b._pos._x + b._size._x >= a._pos._x && b._pos._y + b._size._y >= a._pos._y && b._pos._x + b._size._x <= a._pos._x + a._size._x && b._pos._y + b._size._y <= a._pos._y + a._size._y) {
		return true;
	}
	else if (b._pos._x + b._size._x >= a._pos._x && b._pos._y >= a._pos._y && b._pos._x + b._size._x <= a._pos._x + a._size._x && b._pos._y <= a._pos._y + a._size._y) {
		return true;
	}
	else if (b._pos._x >= a._pos._x && b._pos._y + b._size._y >= a._pos._y && b._pos._x <= a._pos._x + a._size._x && b._pos._y + b._size._y <= a._pos._y + a._size._y) {
		return true;
	}
	return false;
}

bool operator==(Form& a, Position& b) {
	if (b._x >= a._pos._x && b._y >= a._pos._y && b._x <= a._pos._x + a.GetWidth() && b._y <= a._pos._y + a.GetHeight()) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------
//                                        Buttom
//----------------------------------------------------------------------------------------------------

void Button::Draw() {
	sf::Color col = _color;

	if (_state == State::Focused) {
		col.r = abs((col.r + 30) % 256);
		col.g = abs((col.g + 30) % 256);
		col.b = abs((col.b + 30) % 256);
	}
	else if (_state == State::Active) {
		col.r = abs((col.r - 30) % 256);
		col.g = abs((col.g - 30) % 256);
		col.b = abs((col.b - 30) % 256);
	}

	if (!_rounding) {
		sf::RectangleShape rect;

		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_size._x, _size._y));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}
	else {
		RoundedRectangleShape rect;

		rect.setCornersRadius(4);
		rect.setCornerPointCount(5);
		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_size._x, _size._y));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}

	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text info("", font, 20);

	switch (_action) {
		case None:
			break;
		case OK:
			info.setString("OK");
			break;
		case Cancel:
			info.setString("Cancel");
			break;
		case Left:
			info.setString(L'←');
			break;
		case Right:
			info.setString(L'→');
			break;
		case Up:
			info.setString(L'↑');
			break;
		case Down:
			info.setString(L'↓');
			break;
		case Trail:
			info.setString(L'○');
			break;
		case ReadFromFile:
			info.setString("Read from file");
			break;
		case SaveToFile:
			info.setString("Save to file");
			break;
		case Add:
			info.setString("Add");
			break;
		case Delete:
			info.setString("Delete");
			break;
		case Next:
			info.setString("Next");
			break;
		case Prev:
			info.setString("Prev");
			break;
		case SelectColor:
			info.setString("Color");
			break;
		case SelectScale:
			info.setString("Scale");
			break;
		case Hide_Show:
			info.setString("Hide/Show");
			break;
		case Clear:
			info.setString("Clear");
			break;
		case circ:
			info.setString("Circle");
			break;
		case rect:
			info.setString("Rectangle");
			break;
		case triang:
			info.setString("Triangle");
			break;
		case unit:
			info.setString("Unit shape");
			break;
		default:
			break;
	}

	sf::FloatRect area = info.getLocalBounds();
	info.setOrigin(area.width / 2, area.height / 2 + info.getLineSpacing() + 5);
	info.setPosition(sf::Vector2f(_pos._x + _size._x / 2, _pos._y + _size._y / 2));

	_window->draw(info);
}

//----------------------------------------------------------------------------------------------------
//                                        TextBox
//----------------------------------------------------------------------------------------------------

void TextBox::Draw() {
	sf::Color col = _color;

	if (_state == State::Focused) {
		col.r = abs((col.r + 30) % 256);
		col.g = abs((col.g + 30) % 256);
		col.b = abs((col.b + 30) % 256);
	}
	else if (_state == State::Active) {
		col.r = abs((col.r - 30) % 256);
		col.g = abs((col.g - 30) % 256);
		col.b = abs((col.b - 30) % 256);
	}

	if (!_rounding) {
		sf::RectangleShape rect;

		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_size._x, _size._y));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}
	else {
		RoundedRectangleShape rect;

		rect.setCornersRadius(4);
		rect.setCornerPointCount(5);
		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_size._x, _size._y));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}
}

//----------------------------------------------------------------------------------------------------
//                                        Panel
//----------------------------------------------------------------------------------------------------

bool Panel::OnPanel(Form& form) {
	if (form.GetPosition()._x >= this->GetPosition()._x && form.GetPosition()._y >= this->GetPosition()._y &&
		form.GetPosition()._x + form.GetWidth() <= this->GetPosition()._x + this->GetWidth() && form.GetPosition()._y + form.GetHeight() <= this->GetPosition()._y + this->GetHeight()) {
		return true;
	}
	return false;
}

bool Panel::CheckOverlay(Form& form) {
	if (std::find(_elem.begin(), _elem.end(), form) == _elem.end()) {
		return true;
	}
	return false;
}

void Panel::Add(Form& form) {
	if(this->CheckOverlay(form) && this->OnPanel(form)) { 
		Form* temp = form.Clone();
		_elem.push_back(temp);
	}
	else {
		throw "Incorrect position";
	}
}

void Panel::Draw() {
	if (!_rounding) {
		sf::RectangleShape rect;

		rect.setSize(sf::Vector2f(_size._x, _size._y));

		rect.setPosition(_pos._x, _pos._y);

		rect.setFillColor(_color);
		rect.setOutlineColor(sf::Color(abs((_color.r - 30) % 256), abs((_color.g - 30) % 256), abs((_color.b - 30) % 256)));
		rect.setOutlineThickness(4);

		_window->draw(rect);
	}
	else {
		RoundedRectangleShape rect;

		rect.setCornersRadius(4);
		rect.setCornerPointCount(5);
		rect.setFillColor(_color);
		rect.setSize(sf::Vector2f(_size._x, _size._y));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((_color.r - 30) % 256), abs((_color.g - 30) % 256), abs((_color.b - 30) % 256)));

		_window->draw(rect);
	}

	for (auto a : _elem) {
		a->Draw();
	}
}
