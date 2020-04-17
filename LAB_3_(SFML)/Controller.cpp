#pragma warning(disable : 4996)

#include "Controller.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Main window
//----------------------------------------------------------------------------------------------------

void Controller::InitApp()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //ShowWindow(GetConsoleWindow(), SW_SHOW);

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW, settings);
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false, mouse_pressed_on_button = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    SetInterface(window, inter);

    FIGURES.push_back(new Rectangle(window, 100, 100, 50, 50, sf::Color(155, 155, 200)));
    FIGURES.push_back(new Rectangle(window, 300, 300, 50, 50, sf::Color(50, 50, 50)));
    FIGURES.push_back(new Circle(window, 400, 300, 50, sf::Color(10, 10, 10)));

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

                if (!mouse_pressed)
                {
                    focus = inter.CheckFocused(cursor.x, cursor.y);
                    inter.DrawFocus(focus);
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Left && focus != nullptr)
                {
                    focus->SetState(State::Active);
                    focus->Draw();

                    mouse_pressed_on_button = true;
                }

                mouse_pressed = true;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (mouse_pressed_on_button)
                {
                    ShortAction(window, focus);
                }

                focus = inter.CheckFocused(cursor.x, cursor.y);
                inter.DrawFocus(focus);

                mouse_pressed_on_button = false;
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

        if (mouse_pressed_on_button && focus != nullptr)
        {
            LongAction(window, focus);
        }

        DrawFigures();

        window->display();
        window->clear();
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Set interface
//----------------------------------------------------------------------------------------------------

void Controller::SetInterface(std::shared_ptr<sf::RenderWindow> window, Interface& inter)
{
    sf::RectangleShape background;

    background.setSize(sf::Vector2f(SC_WIDTH, SC_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    Panel temp(window, SC_WIDTH / 4 * 3 + 4, 4, SC_WIDTH / 4 - 8, SC_HEIGHT - 8, PANEL_COLOR, State::Inactive);

    Button but1(window, Token::ReadFromFile, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 25 * DIFFERENCE }, BIG_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but2(window, Token::SaveToFile, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 89 * DIFFERENCE }, BIG_BUT, BUTTOM_COLOR, State::Inactive, true);

    Button but3(window, Token::Up, { SC_WIDTH / 4 * 3 + 135 * DIFFERENCE, 208 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but4(window, Token::Left, { SC_WIDTH / 4 * 3 + 70 * DIFFERENCE, 273 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but5(window, Token::Trail, { SC_WIDTH / 4 * 3 + 135 * DIFFERENCE, 273 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but6(window, Token::Right, { SC_WIDTH / 4 * 3 + 200 * DIFFERENCE, 273 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but7(window, Token::Down, { SC_WIDTH / 4 * 3 + 135 * DIFFERENCE, 338 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but8(window, Token::RotateLeft, { SC_WIDTH / 4 * 3 + 75 * DIFFERENCE, 213 * DIFFERENCE }, SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but9(window, Token::RotateRight, Position(SC_WIDTH / 4 * 3 + 195 * DIFFERENCE, 213 * DIFFERENCE), SMALL_BUT, BUTTOM_COLOR, State::Inactive, true);

    Button but10(window, Token::Delete, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 454 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but11(window, Token::Add, { SC_WIDTH / 4 * 3 + 168 * DIFFERENCE, 454 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but12(window, Token::Prev, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 519 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but13(window, Token::Next, { SC_WIDTH / 4 * 3 + 168 * DIFFERENCE, 519 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but14(window, Token::Hide_Show, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 584 * DIFFERENCE }, BIG_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but15(window, Token::SelectColor, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 649 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but16(window, Token::SelectScale, { SC_WIDTH / 4 * 3 + 168 * DIFFERENCE, 649 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

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

//----------------------------------------------------------------------------------------------------
//                                        Draw figures
//----------------------------------------------------------------------------------------------------

void Controller::DrawFigures()
{
    if (COLLIDING_FIGURES.size() == 0)
    {
        for (auto figure : FIGURES)
        {
            figure->Draw();
        }

        if (FIGURES.size() != 0)
        {
            FIGURES[INDEX]->Draw();
        }
    }
    else
    {
        for (auto figure : FIGURES)
        {
            bool flag = true;

            for (auto colliding_figure : COLLIDING_FIGURES)
            {
                if (figure == colliding_figure)
                {
                    flag = false; break;
                }
            }

            if (figure != FIGURES[INDEX] && flag)
            {
                figure->Draw();
            }
        }

        sf::Color temp;

        for (auto figure : COLLIDING_FIGURES)
        {
            temp = figure->GetColor();
            figure->SetColor(collision_color);

            figure->Draw();

            figure->SetColor(temp);
        }

        temp = FIGURES[INDEX]->GetColor();
        FIGURES[INDEX]->SetColor(collision_color);

        FIGURES[INDEX]->Draw();

        FIGURES[INDEX]->SetColor(temp);
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Long action
//----------------------------------------------------------------------------------------------------

void Controller::LongAction(std::shared_ptr<sf::RenderWindow> window, Form* action)
{
    if (FIGURES.size() != 0)
    {
        switch (dynamic_cast<Button*>(action)->GetToken())
        {
        case Token::Up:
        {
            FIGURES[INDEX]->Move(0, -2);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Move(0, 1);

            break;
        }
        case Token::Left:
        {
            FIGURES[INDEX]->Move(-2, 0);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Move(1, 0);

            break;
        }
        case Token::Right:
        {
            FIGURES[INDEX]->Move(2, 0);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Move(-1, 0);

            break;
        }
        case Token::Down:
        {
            FIGURES[INDEX]->Move(0, 2);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Move(0, -1);

            break;
        }
        case Token::RotateLeft:
        {
            FIGURES[INDEX]->Rotate(-1);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Rotate(1);

            break;
        }
        case Token::RotateRight:
        {
            FIGURES[INDEX]->Rotate(1);
            if (!FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) FIGURES[INDEX]->Rotate(-1);

            break;
        }
        default:
            break;
        }

        CheckCollision(INDEX);
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Short action
//----------------------------------------------------------------------------------------------------

void Controller::ShortAction(std::shared_ptr<sf::RenderWindow> window, Form* action)
{
    switch (dynamic_cast<Button*>(action)->GetToken())
    {
    case Token::ReadFromFile:
    {
        window->setVisible(false);
        std::string file = Dialog::OpenFileDialog();
        FIGURES = Parser::ReadFromFile(file);
        window->setVisible(true);

        break;
    }
    case Token::SaveToFile:
    {
        window->setVisible(false);
        std::string file = Dialog::OpenFileDialog();
        Parser::SaveToFile(file, FIGURES);
        window->setVisible(true);

        break;
    }
    case Token::Trail:
    {
        //////////////////////
        break;
    }
    case Token::Delete:
    {
        if (FIGURES.size() != 0)
        {
            std::vector<Shape*> temp;

            for (auto a : FIGURES)
            {
                if (a != FIGURES[INDEX])
                {
                    temp.push_back(a);
                }
            }

            FIGURES = temp;

            if (INDEX != 0)
            {
                INDEX--;
            }
        }

        if(FIGURES.size() != 0) CheckCollision(INDEX);

        break;
    }
    case Token::Add:
    {
        window->setVisible(false);
        Shape* shape = Dialog::OpenFiguresDialog();
        window->setVisible(true);

        if (shape != nullptr)
        {
            FIGURES.push_back(shape);
            INDEX = FIGURES.size() - 1;
        }

        CheckCollision(INDEX);

        break;
    }
    case Token::Prev:
    {
        if (FIGURES.size() != 0)
        {
            FIGURES[INDEX]->SetOutlineThickness(false);

            if (FIGURES.size() > 1)
            {
                INDEX = abs(INDEX - 1) % FIGURES.size();
            }

            if (!FIGURES[INDEX]->GetVisible())
            {
                FIGURES[INDEX]->SetOutlineThickness(true);
            }

            CheckCollision(INDEX);
        }

        break;
    }
    case Token::Next:
    {
        if (FIGURES.size() != 0)
        {
            FIGURES[INDEX]->SetOutlineThickness(false);

            if (FIGURES.size() > 1)
            {
                INDEX = abs(INDEX + 1) % FIGURES.size();
            }

            if (!FIGURES[INDEX]->GetVisible())
            {
                FIGURES[INDEX]->SetOutlineThickness(true);
            }

            CheckCollision(INDEX);
        }

        break;
    }
    case Token::Hide_Show:
    {
        if (FIGURES.size() != 0)
        {
            if (FIGURES[INDEX]->GetVisible())
            {
                FIGURES[INDEX]->SetVisible(false);
                FIGURES[INDEX]->SetOutlineThickness(true);
            }
            else
            {
                FIGURES[INDEX]->SetVisible(true);
                FIGURES[INDEX]->SetOutlineThickness(false);
            }

            CheckCollision(INDEX);
        }

        break;
    }
    case Token::SelectColor:
    {
        window->setVisible(false);
        sf::Color color = Dialog::OpenColorDialog();
        window->setVisible(true);

        CheckCollision(INDEX);

        break;
    }
    case Token::SelectScale:
    {
        window->setVisible(false);
        Position scale = Dialog::OpenScaleDialog();
        window->setVisible(true);

        CheckCollision(INDEX);

        break;
    }
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Check collision
//----------------------------------------------------------------------------------------------------

void Controller::CheckCollision(int INDEX)
{
    COLLIDING_FIGURES = std::vector<Shape*>();

    if (FIGURES[INDEX]->GetVisible())
    {
        int r = 0, g = 0, b = 0;

        bool flag = false;

        for (auto a : FIGURES)
        {
            if (a != FIGURES[INDEX] && Shape::CheckÑollision(FIGURES[INDEX], a) && a->GetVisible())
            {
                COLLIDING_FIGURES.push_back(a);

                r += a->GetColor().r;
                g += a->GetColor().g;
                b += a->GetColor().b;

                flag = true;
            }
        }

        if (flag)
        {
            r += FIGURES[INDEX]->GetColor().r;
            g += FIGURES[INDEX]->GetColor().g;
            b += FIGURES[INDEX]->GetColor().b;

            r /= COLLIDING_FIGURES.size() + 1;
            g /= COLLIDING_FIGURES.size() + 1;
            b /= COLLIDING_FIGURES.size() + 1;

            collision_color.r = r;
            collision_color.g = g;
            collision_color.b = b;
        }
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Instruction
//----------------------------------------------------------------------------------------------------

void Controller::Instruction(std::shared_ptr<sf::RenderWindow> window)
{

}
