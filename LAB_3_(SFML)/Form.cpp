#include "Form.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Buttom
//----------------------------------------------------------------------------------------------------

void Button::Draw()
{
	sf::Color col = _color;

	if (_state == State::Focused)
	{
		col.r = abs((col.r + 30) % 256);
		col.g = abs((col.g + 30) % 256);
		col.b = abs((col.b + 30) % 256);
	}
	else if (_state == State::Active)
	{
		col.r = abs((col.r - 30) % 256);
		col.g = abs((col.g - 30) % 256);
		col.b = abs((col.b - 30) % 256);
	}

	if (!_rounding)
	{
		sf::RectangleShape rect;

		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_width, _height));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}
	else
	{
		RoundedRectangleShape rect;

		rect.setCornersRadius(4);
		rect.setCornerPointCount(5);
		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_width, _height));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((col.r - 30) % 256), abs((col.g - 30) % 256), abs((col.b - 30) % 256)));

		_window->draw(rect);
	}
}

//----------------------------------------------------------------------------------------------------
//                                        Panel
//----------------------------------------------------------------------------------------------------

bool Panel::OnPanel(Form& form)
{
	if (form.GetPosition()._x >= this->GetPosition()._x && form.GetPosition()._y >= this->GetPosition()._y &&
		form.GetPosition()._x + form.GetWidth() <= this->GetPosition()._x + this->GetWidth() && form.GetPosition()._y + form.GetHeight() <= this->GetPosition()._y + this->GetHeight())
	{
		return true;
	}
	else return false;
}

bool Panel::CheckOverlay(Form& form)
{
	for (auto a : _elem)
	{
		if (*a == form)
		{
			return false;
		}
	}

	return true;
}

void Panel::Add(Form& form)
{
	if(this->CheckOverlay(form) && this->OnPanel(form))
	{ 
		Form* temp = form.Clone();

		_elem.push_back(temp);
	}
	else
	{
		throw "Incorrect position";
	}
}

void Panel::Draw()
{
	if (!_rounding)
	{
		sf::RectangleShape rect;

		rect.setSize(sf::Vector2f(_width, _height));

		rect.setPosition(_pos._x, _pos._y);

		rect.setFillColor(_color);
		rect.setOutlineColor(sf::Color(abs((_color.r - 30) % 256), abs((_color.g - 30) % 256), abs((_color.b - 30) % 256)));
		rect.setOutlineThickness(4);

		_window->draw(rect);
	}
	else
	{
		RoundedRectangleShape rect;

		rect.setCornersRadius(4);
		rect.setCornerPointCount(5);
		rect.setFillColor(_color);
		rect.setSize(sf::Vector2f(_width, _height));
		rect.setPosition(_pos._x, _pos._y);
		rect.setOutlineThickness(4);
		rect.setOutlineColor(sf::Color(abs((_color.r - 30) % 256), abs((_color.g - 30) % 256), abs((_color.b - 30) % 256)));

		_window->draw(rect);
	}

	for (auto a : _elem)
	{
		a->Draw();
	}
}

//----------------------------------------------------------------------------------------------------
//                                        Form
//----------------------------------------------------------------------------------------------------

bool operator==(Form& a, Form& b)
{
	if(a._pos._x >= b._pos._x && a._pos._y >= b._pos._y && a._pos._x <= b._pos._x + b._width && a._pos._y <= b._pos._y + b._height)
	{ 
		return true;
	}
	else if (a._pos._x + a._width >= b._pos._x && a._pos._y + a._height >= b._pos._y && a._pos._x + a._width <= b._pos._x + b._width && a._pos._y + a._height <= b._pos._y + b._height)
	{
		return true;
	}
	else if (a._pos._x + a._width >= b._pos._x && a._pos._y >= b._pos._y && a._pos._x + a._width <= b._pos._x + b._width && a._pos._y <= b._pos._y + b._height)
	{
		return true;
	}
	else if (a._pos._x >= b._pos._x && a._pos._y + a._height >= b._pos._y && a._pos._x <= b._pos._x + b._width && a._pos._y + a._height <= b._pos._y + b._height)
	{
		return true;
	}

	if (b._pos._x >= a._pos._x && b._pos._y >= a._pos._y && b._pos._x <= a._pos._x + a._width && b._pos._y <= a._pos._y + a._height)
	{
		return true;
	}
	else if (b._pos._x + b._width >= a._pos._x && b._pos._y + b._height >= a._pos._y && b._pos._x + b._width <= a._pos._x + a._width && b._pos._y + b._height <= a._pos._y + a._height)
	{
		return true;
	}
	else if (b._pos._x + b._width >= a._pos._x && b._pos._y >= a._pos._y && b._pos._x + b._width <= a._pos._x + a._width && b._pos._y <= a._pos._y + a._height)
	{
		return true;
	}
	else if (b._pos._x >= a._pos._x && b._pos._y + b._height >= a._pos._y && b._pos._x <= a._pos._x + a._width && b._pos._y + b._height <= a._pos._y + a._height)
	{
		return true;
	}

	return false;
}

bool operator==(Form& a, Position& b)
{
	if (b._x >= a._pos._x && b._y >= a._pos._y && b._x <= a._pos._x + a.GetWidth() && b._y <= a._pos._y + a.GetHeight())
	{
		return true;
	}

	return false;
}
