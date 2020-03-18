#include "Controller.hpp"
#include <string>

//----------------------------------------------------------------------------------------------------
//                                        Controller
//----------------------------------------------------------------------------------------------------

void Controller::InitApp()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW, settings);
    sf::RenderWindow* ptr_window = &window;
    
    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    SetInterface(ptr_window, inter);

    Triangle tr(ptr_window);

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

                if (!mouse_pressed)
                {
                    inter.DrawFocus(focus);
                }

                tr.Rotate(1);
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();
                    Action(focus);
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

        for (auto figure : FIGURES)
        {
            figure->Draw();
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
    background.setFillColor(BACKGROUND_COLOR);

    Panel temp(window, Position(SC_WIDTH/4 * 3 + 4, 4), SC_WIDTH/4 - 8, SC_HEIGHT - 8, PANEL_COLOR, State::Inactive);

    Button but1(window, Token::ReadFromFile, Position(SC_WIDTH / 4 * 3 + 28, 25), BIG_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but2(window, Token::SaveToFile, Position(SC_WIDTH / 4 * 3 + 28, 89), BIG_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    Button but3(window, Token::Up, Position(SC_WIDTH / 4 * 3 + 135, 208), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but4(window, Token::Left, Position(SC_WIDTH / 4 * 3 + 70, 273), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but5(window, Token::Trail, Position(SC_WIDTH / 4 * 3 + 135, 273), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but6(window, Token::Right, Position(SC_WIDTH / 4 * 3 + 200, 273), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but7(window, Token::Down, Position(SC_WIDTH / 4 * 3 + 135, 338), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but8(window, Token::RotateLeft, Position(SC_WIDTH / 4 * 3 + 75, 213), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but9(window, Token::RotateRight, Position(SC_WIDTH / 4 * 3 + 195, 213), SMALL_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    Button but10(window, Token::Delete, Position(SC_WIDTH / 4 * 3 + 28, 454), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but11(window, Token::Add, Position(SC_WIDTH / 4 * 3 + 168, 454), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but12(window, Token::Prev, Position(SC_WIDTH / 4 * 3 + 28, 519), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but13(window, Token::Next, Position(SC_WIDTH / 4 * 3 + 168, 519), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but14(window, Token::Hide_Show, Position(SC_WIDTH / 4 * 3 + 28, 584), BIG_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but15(window, Token::SelectColor, Position(SC_WIDTH / 4 * 3 + 28, 649), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);
    Button but16(window, Token::SelectScale, Position(SC_WIDTH / 4 * 3 + 168, 649), STANDARD_BUT, BUTTOM_COLOR, sf::Sprite(), State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    temp.Add(but3);
    temp.Add(but4);
    temp.Add(but5);
    temp.Add(but6);
    temp.Add(but7);
    temp.Add(but8);
    temp.Add(but9);

    temp.Add(but10);
    temp.Add(but11);
    temp.Add(but12);
    temp.Add(but13);
    temp.Add(but14);
    temp.Add(but15);
    temp.Add(but16);

    inter.SetWindow(window);
    inter.SetBackground(background);
    inter.AddPanel(temp);
}

void Controller::Action(Form* action)
{
    switch (dynamic_cast<Button*>(action)->GetToken())
    {
    case Token::ReadFromFile:
    {
        std::string file = OpenFileDialog();

        break;
    }
    case Token::SaveToFile:
    {
        std::string file = OpenFileDialog();

        break;
    }
    case Token::Up:
    {
        FIGURES[INDEX]->Move(0, -1);

        break;
    }
    case Token::Left:
    {
        FIGURES[INDEX]->Move(-1, 0);

        break;
    }
    case Token::Trail:
    {
        break;
    }
    case Token::Right:
    {
        FIGURES[INDEX]->Move(1, 0);

        break;
    }
    case Token::Down:
    {
        FIGURES[INDEX]->Move(0, 1);

        break;
    }
    case Token::RotateLeft:
    {
        break;
    }
    case Token::RotateRight:
    {
        break;
    }
    case Token::Delete:
    {

        break;
    }
    case Token::Add:
    {
        FIGURES.push_back(OpenFiguresDialog());

        break;
    }
    case Token::Prev:
    {
        break;
    }
    case Token::Next:
    {
        break;
    }
    case Token::Hide_Show:
    {
        break;
    }
    case Token::SelectColor:
    {
        sf::Color color = OpenColorDialog();
        break;
    }
    case Token::SelectScale:
    {
        Position scale = OpenScaleDialog();
        break;
    }
    default:
        break;
    }
}

std::string Controller::OpenFileDialog()
{
    sf::RenderWindow window(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "Выбор файла", WINDOW);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(MSG_WIDTH, MSG_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    inter.SetBackground(background);

    return std::string();
}

Shape* Controller::OpenFiguresDialog()
{
    sf::RenderWindow window(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "Выбор фигуры", WINDOW);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(MSG_WIDTH, MSG_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    inter.SetBackground(background);

    return nullptr;
}

sf::Color Controller::OpenColorDialog()
{
    sf::RenderWindow window(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "Выбор цвета", WINDOW);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(MSG_WIDTH, MSG_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    inter.SetBackground(background);

    return sf::Color();
}

Position Controller::OpenScaleDialog()
{
    sf::RenderWindow window(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "Выбор масштаба", WINDOW);

    sf::Event event;
    bool mouse_pressed = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(MSG_WIDTH, MSG_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    inter.SetBackground(background);

    return Position();
}

void Controller::Instruction(sf::RenderWindow* window)
{

}
