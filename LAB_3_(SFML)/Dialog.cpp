#include "Dialog.hpp"

//----------------------------------------------------------------------------------------------------
//                                        File dialog
//----------------------------------------------------------------------------------------------------

std::string Dialog::OpenFileDialog()
{
    std::string file_name;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3");
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, 0, 0, MSG_WIDTH, MSG_HEIGHT, PANEL_COLOR, State::Inactive);
    Button but1(window, Token::OK, { MSG_WIDTH / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 3 / 4 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp);

    while (window->isOpen())
    {
        inter.Draw();

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
            {
                cursor = sf::Mouse::getPosition(*window);
                focus = inter.CheckFocused(cursor.x, cursor.y);

                if (!mouse_pressed)
                {
                    inter.DrawFocus(focus);
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();

                    switch (dynamic_cast<Button*>(focus)->GetToken())
                    {
                    case Token::OK:
                    {
                        return file_name;
                    }
                    case Token::Cancel:
                    {
                        window->close();
                        break;
                    }
                    default:
                        break;
                    }
                }

                mouse_pressed = true;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                inter.DrawFocus(focus);

                mouse_pressed = false;
                break;
            }
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;
            }
            default:
                break;
            }
        }

        window->display();
        window->clear();
    }

    return std::string();
}

//----------------------------------------------------------------------------------------------------
//                                        Figures dialog
//----------------------------------------------------------------------------------------------------

Shape* Dialog::OpenFiguresDialog()
{
    Shape* shape = nullptr;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW);
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, 0, 0, MSG_HEIGHT, MSG_WIDTH, PANEL_COLOR, State::Inactive);
    Button but1(window, Token::circ, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but2(window, Token::rect, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 2 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but3(window, Token::triang, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 3 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but4(window, Token::unit, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 4 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but5(window, Token::Cancel, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2 , MSG_WIDTH * 5 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);
    temp.Add(but3);
    temp.Add(but4);
    temp.Add(but5);

    inter.SetWindow(window);
    inter.AddPanel(temp);

    while (window->isOpen())
    {
        inter.Draw();

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
            {
                cursor = sf::Mouse::getPosition(*window);
                focus = inter.CheckFocused(cursor.x, cursor.y);

                if (!mouse_pressed)
                {
                    inter.DrawFocus(focus);
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();

                    switch (dynamic_cast<Button*>(focus)->GetToken())
                    {
                    case Token::OK:
                    {
                        return shape;
                    }
                    case Token::Cancel:
                    {
                        window->close();
                        break;
                    }
                    default:
                        break;
                    }
                }

                mouse_pressed = true;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                inter.DrawFocus(focus);

                mouse_pressed = false;
                break;
            }
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;
            }
            default:
                break;
            }
        }

        window->display();
        window->clear();
    }

    return nullptr;
}

//----------------------------------------------------------------------------------------------------
//                                        Color dialog
//----------------------------------------------------------------------------------------------------

sf::Color Dialog::OpenColorDialog()
{
    sf::Color color;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW);
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, 0, 0, MSG_WIDTH, MSG_HEIGHT, PANEL_COLOR, State::Inactive);
    Button but1(window, Token::OK, { MSG_WIDTH / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 3 / 4 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp);

    while (window->isOpen())
    {
        inter.Draw();

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
            {
                cursor = sf::Mouse::getPosition(*window);
                focus = inter.CheckFocused(cursor.x, cursor.y);

                if (!mouse_pressed)
                {
                    inter.DrawFocus(focus);
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();

                    switch (dynamic_cast<Button*>(focus)->GetToken())
                    {
                    case Token::OK:
                    {
                        return color;
                    }
                    case Token::Cancel:
                    {
                        window->close();
                        break;
                    }
                    default:
                        break;
                    }
                }

                mouse_pressed = true;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                inter.DrawFocus(focus);

                mouse_pressed = false;
                break;
            }
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;
            }
            default:
                break;
            }
        }

        window->display();
        window->clear();
    }

    return sf::Color();
}

//----------------------------------------------------------------------------------------------------
//                                        Scale dialog
//----------------------------------------------------------------------------------------------------

Position Dialog::OpenScaleDialog()
{
    Position pos;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW);
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, 0, 0, MSG_WIDTH, MSG_HEIGHT, PANEL_COLOR, State::Inactive);
    Button but1(window, Token::OK, { MSG_WIDTH / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 3 / 4 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp);

    while (window->isOpen())
    {
        inter.Draw();

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
            {
                cursor = sf::Mouse::getPosition(*window);
                focus = inter.CheckFocused(cursor.x, cursor.y);

                if (!mouse_pressed)
                {
                    inter.DrawFocus(focus);
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();

                    switch (dynamic_cast<Button*>(focus)->GetToken())
                    {
                    case Token::OK:
                    {
                        return pos;
                    }
                    case Token::Cancel:
                    {
                        window->close();
                        break;
                    }
                    default:
                        break;
                    }
                }

                mouse_pressed = true;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                inter.DrawFocus(focus);

                mouse_pressed = false;
                break;
            }
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;
            }
            default:
                break;
            }
        }

        window->display();
        window->clear();
    }

    return Position();
}