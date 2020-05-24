#pragma warning(disable : 4996)

#include "Controller.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Main window
//----------------------------------------------------------------------------------------------------

void Controller::InitApp() {
    //ShowWindow(GetConsoleWindow(), SW_SHOW);
    srand(time(NULL));

    // Settings //
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window //
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "LAB_3", WINDOW, settings);
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);
    MAIN_WINDOW = window;
    MODE = WINDOW_MODE::Standard;

    // Timer //
    sf::Clock timer;

    // Event //
    sf::Vector2i cursor;
    Form* focus = nullptr;
    sf::Event event;
    bool mouse_pressed = false, mouse_pressed_on_button = false;

    // Interface //
    Interface inter;
    SetInterface(window, inter);

    // Shape factory //
    Factory* fac = new Factory(window);

    // Window running... //
    while (window->isOpen()) {
        // Drawing interface... //
        inter.Draw();

        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseMoved: {
                    cursor = sf::Mouse::getPosition(*window);

                    if (!mouse_pressed) {
                        focus = inter.CheckFocused(cursor.x, cursor.y);
                        inter.DrawFocus(focus);
                    }

                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if(event.mouseButton.button == sf::Mouse::Left && focus != nullptr) {
                        focus->SetState(State::Active);
                        focus->Draw();

                        mouse_pressed_on_button = true;
                    }

                    mouse_pressed = true;
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    if (mouse_pressed_on_button) {
                        ShortAction(fac, dynamic_cast<Button*>(focus)->GetToken());
                    }

                    focus = inter.CheckFocused(cursor.x, cursor.y);
                    inter.DrawFocus(focus);

                    mouse_pressed_on_button = false;
                    mouse_pressed = false;
                    break;
                }
                case sf::Event::Closed: {
                    window->close();
                    break;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (!UNIT_FIGURES.empty()) {
                            FIGURES.push_back(new UnitShape(MAIN_WINDOW, UNIT_FIGURES));
                            INDEX = FIGURES.size() - 1;
                        }

                        UNIT_FIGURES.clear();
                        UNIT_INDEX = 0;
                        MODE = WINDOW_MODE::Standard;
                    }
                    else if (event.key.code == sf::Keyboard::Space) {
                        if (MODE == WINDOW_MODE::ShapeSelection && UNIT_INDEX != INDEX) {
                            UNIT_FIGURES.push_back(FIGURES[INDEX]->Clone());
                        }
                    }

                    break;
                }
                default:
                    break;
            }

            timer.restart();
        }

        if (mouse_pressed_on_button && focus != nullptr) {
            LongAction(dynamic_cast<Button*>(focus)->GetToken());
            timer.restart();
        }

        // Timer check... //
        if (timer.getElapsedTime().asSeconds() > TIMER && MODE != WINDOW_MODE::ShapeSelection) {
            MODE = WINDOW_MODE::Standby;
        }
        else if (timer.getElapsedTime().asSeconds() < TIMER && MODE != WINDOW_MODE::ShapeSelection) {
            MODE = WINDOW_MODE::Standard;
        }

        // Drawing shapes... //
        DrawFigures(MODE);

        window->display();
        window->clear();
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Set interface
//----------------------------------------------------------------------------------------------------

void Controller::SetInterface(std::shared_ptr<sf::RenderWindow> window, Interface& inter) {
    sf::RectangleShape background;

    background.setSize(sf::Vector2f(SC_WIDTH, SC_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(BACKGROUND_COLOR);

    Panel temp(window, { SC_WIDTH / 4 * 3 + 4, 4 }, { SC_WIDTH / 4 - 8, SC_HEIGHT - 8 }, PANEL_COLOR, State::Inactive);

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
    Button but14(window, Token::Hide_Show, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 584 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but15(window, Token::Clear, { SC_WIDTH / 4 * 3 + 168 * DIFFERENCE, 584 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but16(window, Token::SelectColor, { SC_WIDTH / 4 * 3 + 28 * DIFFERENCE, 649 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but17(window, Token::SelectScale, { SC_WIDTH / 4 * 3 + 168 * DIFFERENCE, 649 * DIFFERENCE }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

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
    temp.Add(but17);

    inter.SetWindow(window);
    inter.SetBackground(background);
    inter.AddPanel(temp);
}

//----------------------------------------------------------------------------------------------------
//                                        Draw figures
//----------------------------------------------------------------------------------------------------

void Controller::DrawFigures(WINDOW_MODE mode) {
    if (mode == WINDOW_MODE::Standby) {
        for (auto shape : FIGURES) {
            if (shape->GetMove() == Position(0, 0)) {
                shape->SetMove(Position(rand() % 3, rand() % 3));
            }
        }

        for (auto figure : FIGURES) {
            figure->Draw();
        }
    }
    else {
        for (auto shape : FIGURES) {
            shape->SetMove({0, 0});
        }

        if (FIGURES.size() != 0) {
            CheckCollision(INDEX);
        }

        if (COLLIDING_FIGURES.size() == 0) {
            for (auto figure : FIGURES) {
                figure->Draw();
            }

            if (FIGURES.size() != 0) {
                FIGURES[INDEX]->Draw();
            }
        }
        else {
            for (auto figure : FIGURES) {
                bool flag = true;

                for (auto colliding_figure : COLLIDING_FIGURES) {
                    if (figure == colliding_figure) {
                        flag = false; break;
                    }
                }

                if (figure != FIGURES[INDEX] && flag) {
                    figure->Draw();
                }
            }

            sf::Color temp;

            for (auto figure : COLLIDING_FIGURES) {
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
}

//----------------------------------------------------------------------------------------------------
//                                        Long action
//----------------------------------------------------------------------------------------------------

void Controller::LongAction(Token token) {
    if (FIGURES.size() != 0) {
        switch (token) {
            case Token::Up: {
                FIGURES[INDEX]->Move(MOVE_UP);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Move(MOVE_DOWN);
                }

                break;
            }
            case Token::Left: {
                FIGURES[INDEX]->Move(MOVE_LEFT);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Move(MOVE_RIGHT);
                }

                break;
            }
            case Token::Right: {
                FIGURES[INDEX]->Move(MOVE_RIGHT);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Move(MOVE_LEFT);
                }

                break;
            }
            case Token::Down: {
                FIGURES[INDEX]->Move(MOVE_DOWN);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Move(MOVE_UP);
                }

                break;
            }
            case Token::RotateLeft: {
                FIGURES[INDEX]->Rotate(ROTATE_LEFT);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Rotate(ROTATE_RIGHT);
                }

                break;
            }
            case Token::RotateRight: {
                FIGURES[INDEX]->Rotate(ROTATE_RIGHT);
                if (FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) != SIDE::NONE_SIDE) {
                    FIGURES[INDEX]->Rotate(ROTATE_LEFT);
                }

                break;
            }
            default:
                break;
        }
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Short action
//----------------------------------------------------------------------------------------------------

void Controller::ShortAction(Factory* fac, Token token) {
    switch (token) {
        case Token::ReadFromFile: {
            std::string file = Dialog::OpenFileDialog();

            std::cout << file << std::endl;

            if (file != std::string()) {
                FIGURES = InfoManager::ReadFromFile(file);
            }

            for (auto a : FIGURES) {
                a->SetWindow(MAIN_WINDOW);
            }

            break;
        }
        case Token::SaveToFile: {
            std::string file = Dialog::OpenFileDialog();
            InfoManager::SaveToFile(file, FIGURES);

            break;
        }
        case Token::Trail: {
            if (FIGURES.size() != 0) {
                FIGURES[INDEX]->SetTail(FIGURES[INDEX]->GetTail() ? false : true);
            }

            break;
        }
        case Token::Delete: {
            if (FIGURES.size() != 0) {
                std::vector<Shape*> temp;

                for (auto a : FIGURES) {
                    if (a != FIGURES[INDEX]) {
                        temp.push_back(a);
                    }
                }

                FIGURES = temp;

                if (INDEX != 0) {
                    INDEX--;
                }
            }

            break;
        }
        case Token::Add: {
            Shape* shape = Dialog::OpenFiguresDialog(fac);

            if (shape != nullptr) {
                if (shape->GetName() == "unit") {
                    MODE = WINDOW_MODE::ShapeSelection;
                    UNIT_INDEX = FIGURES.size();
                }
                else {
                    FIGURES.push_back(shape);
                    INDEX = FIGURES.size() - 1;
                }
            }

            break;
        }
        case Token::Prev: {
            if (FIGURES.size() != 0) {
                FIGURES[INDEX]->SetOutlineThickness(false);

                if (FIGURES.size() > 1) {
                    INDEX = (FIGURES.size() + INDEX - 1) % FIGURES.size();
                }

                if (!FIGURES[INDEX]->GetVisible()) {
                    FIGURES[INDEX]->SetOutlineThickness(true);
                }
            }

            break;
        }
        case Token::Next: {
            if (FIGURES.size() != 0) {
                FIGURES[INDEX]->SetOutlineThickness(false);

                if (FIGURES.size() > 1) {
                    INDEX = abs(INDEX + 1) % FIGURES.size();
                }

                if (!FIGURES[INDEX]->GetVisible()) {
                    FIGURES[INDEX]->SetOutlineThickness(true);
                }
            }

            break;
        }
        case Token::Hide_Show: {
            if (FIGURES.size() != 0) {
                FIGURES[INDEX]->SetVisible(FIGURES[INDEX]->GetVisible() ? false : true);
                FIGURES[INDEX]->SetOutlineThickness(FIGURES[INDEX]->GetVisible() ? false : true);
            }

            break;
        }
        case Token::Clear:
        {
            FIGURES.clear();
            break;
        }
        case Token::SelectColor: {
            if (FIGURES.size() != 0) {
                sf::Color color = Dialog::OpenColorDialog();

                if (color.a != 0) {
                    FIGURES[INDEX]->SetColor(color);
                }
            }

            break;
        }
        case Token::SelectScale: {
            if (FIGURES.size() != 0) {
                Position scale = Dialog::OpenScaleDialog();
                Position temp = FIGURES[INDEX]->GetScale();
                FIGURES[INDEX]->SetScale(scale);

                if (!(FIGURES[INDEX]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT) == SIDE::NONE_SIDE)) {
                    FIGURES[INDEX]->SetScale(temp);
                }
            }

            break;
        }
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------------
//                                        Check collision
//----------------------------------------------------------------------------------------------------

void Controller::CheckCollision(int INDEX) {
    COLLIDING_FIGURES = std::vector<Shape*>();

    if (FIGURES[INDEX]->GetVisible()) {
        int r = 0, g = 0, b = 0;

        bool flag = false;

        for (auto a : FIGURES) {
            if (a != FIGURES[INDEX] && Shape::CheckÑollision(FIGURES[INDEX], a) && a->GetVisible()) {
                COLLIDING_FIGURES.push_back(a);

                r += a->GetColor().r;
                g += a->GetColor().g;
                b += a->GetColor().b;

                flag = true;
            }
        }

        if (flag) {
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
