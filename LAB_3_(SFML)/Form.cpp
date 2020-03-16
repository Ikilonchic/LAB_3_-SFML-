#include "Form.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Buttom
//----------------------------------------------------------------------------------------------------

void Buttom::Draw()
{
	sf::Color col = _color;

	if (_state == State::Focused)
	{
		col.r += 30;
		col.g += 30;
		col.b += 30;
	}
	else if (_state == State::Active)
	{
		col.r -= 30;
		col.g -= 30;
		col.b -= 30;
	}

	if (!_rounding)
	{
		sf::RectangleShape rect;

		rect.setFillColor(col);
		rect.setSize(sf::Vector2f(_width, _height));
		rect.setPosition(_pos.GetX(), _pos.GetY());
		_window->draw(rect);
	}
	else
	{
		sf::RectangleShape rect;
		sf::CircleShape circle;

		rect.setFillColor(col);
		circle.setFillColor(col);

		rect.setSize(sf::Vector2f(_width - 10, _height));
		rect.setPosition(_pos.GetX() + 5, _pos.GetY());
		_window->draw(rect);

		rect.setSize(sf::Vector2f(_width, _height - 10));
		rect.setPosition(_pos.GetX(), _pos.GetY() + 5);
		_window->draw(rect);

		circle.setRadius(5.f);
		circle.setPosition(sf::Vector2f(_pos.GetX(), _pos.GetY()));
		_window->draw(circle);
		circle.setPosition(sf::Vector2f(_pos.GetX() + _width - 10, _pos.GetY()));
		_window->draw(circle);
		circle.setPosition(sf::Vector2f(_pos.GetX() + _width - 10, _pos.GetY() + _height - 10));
		_window->draw(circle);
		circle.setPosition(sf::Vector2f(_pos.GetX(), _pos.GetY() + _height - 10));
		_window->draw(circle);
	}
}

//----------------------------------------------------------------------------------------------------
//                                        Panel
//----------------------------------------------------------------------------------------------------

bool Panel::OnPanel(Form& form)
{
	if (form.GetPosition().GetX() >= this->GetPosition().GetX() && form.GetPosition().GetY() >= this->GetPosition().GetY() &&
		form.GetPosition().GetX() + form.GetWidth() <= this->GetPosition().GetX() + this->GetWidth() && form.GetPosition().GetY() + form.GetHeight() <= this->GetPosition().GetY() + this->GetHeight())
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

void Panel::AddForm(Form& form)
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
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(_width, _height));

	rect.setPosition(_pos.GetX(), _pos.GetY());

	rect.setFillColor(_color);
	rect.setOutlineColor(sf::Color(((_color.r - 15) % 255), ((_color.g - 15) % 255), ((_color.b - 15) % 255)));
	rect.setOutlineThickness(4);

	_window->draw(rect);

	for (auto a : _elem)
	{
		a->Draw();
	}
}

bool operator==(Form& a, Form& b)
{
	if(a._pos.GetX() >= b._pos.GetX() && a._pos.GetY() >= b._pos.GetY() && a._pos.GetX() <= b._pos.GetX() + b._width && a._pos.GetY() <= b._pos.GetY() + b._height)
	{ 
		return true;
	}
	else if (a._pos.GetX() + a._width >= b._pos.GetX() && a._pos.GetY() + a._height >= b._pos.GetY() && a._pos.GetX() + a._width <= b._pos.GetX() + b._width && a._pos.GetY() + a._height <= b._pos.GetY() + b._height)
	{
		return true;
	}
	else if (a._pos.GetX() + a._width >= b._pos.GetX() && a._pos.GetY() >= b._pos.GetY() && a._pos.GetX() + a._width <= b._pos.GetX() + b._width && a._pos.GetY() <= b._pos.GetY() + b._height)
	{
		return true;
	}
	else if (a._pos.GetX() >= b._pos.GetX() && a._pos.GetY() + a._height >= b._pos.GetY() && a._pos.GetX() <= b._pos.GetX() + b._width && a._pos.GetY() + a._height <= b._pos.GetY() + b._height)
	{
		return true;
	}

	if (b._pos.GetX() >= a._pos.GetX() && b._pos.GetY() >= a._pos.GetY() && b._pos.GetX() <= a._pos.GetX() + a._width && b._pos.GetY() <= a._pos.GetY() + a._height)
	{
		return true;
	}
	else if (b._pos.GetX() + b._width >= a._pos.GetX() && b._pos.GetY() + b._height >= a._pos.GetY() && b._pos.GetX() + b._width <= a._pos.GetX() + a._width && b._pos.GetY() + b._height <= a._pos.GetY() + a._height)
	{
		return true;
	}
	else if (b._pos.GetX() + b._width >= a._pos.GetX() && b._pos.GetY() >= a._pos.GetY() && b._pos.GetX() + b._width <= a._pos.GetX() + a._width && b._pos.GetY() <= a._pos.GetY() + a._height)
	{
		return true;
	}
	else if (b._pos.GetX() >= a._pos.GetX() && b._pos.GetY() + b._height >= a._pos.GetY() && b._pos.GetX() <= a._pos.GetX() + a._width && b._pos.GetY() + b._height <= a._pos.GetY() + a._height)
	{
		return true;
	}

	return false;
}

bool operator==(Form& a, Position& b)
{
	if (b.GetX() >= a._pos.GetX() && b.GetY() >= a._pos.GetY() && b.GetX() <= a._pos.GetX() + a.GetWidth() && b.GetY() <= a._pos.GetY() + a.GetHeight())
	{
		return true;
	}

	return false;
}
