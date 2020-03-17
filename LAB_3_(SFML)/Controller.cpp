#include "Controller.hpp"
//#include <Windows.h>

//----------------------------------------------------------------------------------------------------
//                                        Controller
//----------------------------------------------------------------------------------------------------

void Controller::InitApp()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW, settings);
    sf::RenderWindow* ptr_window = &window;

    sf::Event event;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    SetInterface(ptr_window, inter);

    Rectangle tr(ptr_window, { 200, 200 }, 100, 100, sf::Color(10, 100, 200));
    tr.SetScale(2, 1);

    while (window.isOpen())
    {
        inter.Draw();
        tr.Draw();

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
            {
               cursor = sf::Mouse::getPosition(*ptr_window);
               focus = inter.CheckFocused(cursor.x, cursor.y);

               inter.DrawFocus(focus);

               tr.Rotate(1);

               break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    cursor = sf::Mouse::getPosition(*ptr_window);
                    focus->SetState(State::Active);
                    focus->Draw();
                    focus->SetState(State::Focused);
                }

                break;
            }
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;
            }
            default:
                break;
            }
        }

        window.display();
        window.clear();
    }
}

void Controller::SetInterface(sf::RenderWindow* window, Interface& inter)
{
    sf::RectangleShape background;

    background.setSize(sf::Vector2f(SC_WIDTH, SC_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(130, 130, 130));

    Panel temp(window, Position(SC_WIDTH/4 * 3 + 4, 4), SC_WIDTH/4 - 8, SC_HEIGHT - 8, sf::Color(155, 155, 155));
    Button but1(window, Token::ReadFromFile, Position(SC_WIDTH / 4 * 3 + 10, 10), 30, 30, sf::Color(100, 100, 100), State::Inactive, true);
    Button but2(window, Token::SaveToFile, Position(SC_WIDTH / 4 * 3 + 50, 10), 30, 30, sf::Color(100, 100, 100), State::Inactive, true);
    Button but3(window, Token::None, Position(SC_WIDTH / 4 * 3 + 90, 10), 30, 30, sf::Color(100, 100, 100), State::Inactive, true);

    temp.AddForm(but1);
    temp.AddForm(but2);
    temp.AddForm(but3);

    inter.SetWindow(window);
    inter.SetBackground(background);
    inter.AddPanel(temp);
}

void Controller::Instruction(sf::RenderWindow* window)
{

}