#include "Interface.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Interface
//----------------------------------------------------------------------------------------------------

void Interface::AddPanel(Panel& form)
{
	if(this->CheckOverlay(form))
	{ 
		Panel* temp = new Panel(form);
		_form.push_back(temp);
	}
	else
	{
		throw "Incorrect position";
	}
}

bool Interface::CheckOverlay(Form& form)
{
	for (auto a : _form)
	{
		if (*a == form)
		{
			//return false;
		}
	}

	return true;
}

Form* Interface::CheckFocused(Position& mouse)
{
	Panel* temp = nullptr;

	for (auto a : _form)
	{
		if (*a == mouse)
		{
			temp = a;
			break;
		}
	}

	if (temp != nullptr)
	{
		for (auto a : temp->_elem)
		{
			if (*a == mouse)
			{
				return a;
			}
		}
	}

	return nullptr;
}

Form* Interface::CheckFocused(float x, float y)
{
	Panel* temp = nullptr;
	Position mouse(x, y);

	for (auto a : _form)
	{
		if (*a == mouse)
		{
			temp = a;
			break;
		}
	}

	if (temp != nullptr)
	{
		for (auto a : temp->_elem)
		{
			if (*a == mouse)
			{
				return a;
			}
		}
	}

	return nullptr;
}

void Interface::DrawFocus(Form* focus)
{
	//Вводим форму, на которой фокус:
	
	//Если она не совпадает с предыдущей, прошлую деактивируем, а новую активируем и записываем, как фокус.
	//Если совпадает, то оставляем все как есть.
	//Если NULL, то стираем старую и в фокусе NULL.

	if (focus != nullptr && _focus != nullptr)
	{
		_focus->SetState(State::Inactive);
		_focus->Draw();

		_focus = focus;

		_focus->SetState(State::Focused);
		_focus->Draw();
	}
	else if (focus != nullptr && _focus == nullptr)
	{
		_focus = focus;

		_focus->SetState(State::Focused);
		_focus->Draw();
	}
	else if (focus == nullptr && _focus != nullptr)
	{
		_focus->SetState(State::Inactive);
		_focus->Draw();

		_focus = focus;
	}
}

void Interface::Draw()
{
	_window->draw(_background);

	for (auto a : _form)
	{
		a->Draw();
	}
}
