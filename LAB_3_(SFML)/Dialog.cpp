#include "Dialog.hpp"

//----------------------------------------------------------------------------------------------------
//                                        File dialog
//----------------------------------------------------------------------------------------------------

std::string Dialog::OpenFileDialog() {
    std::string file_name;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "LAB_3");
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    sf::Vector2i cursor;
    sf::Event event;
    bool mouse_pressed = false, mouse_pressed_on_button = false;

    Interface inter;

    Form* focus = nullptr;

    Panel temp1(window, { 0, 0 }, { MSG_WIDTH, MSG_HEIGHT }, PANEL_COLOR, State::Inactive);

    Panel temp2(window, { MSG_WIDTH / 2 - BIG_BUT._x / 2, MSG_HEIGHT / 4 - STANDARD_BUT._y / 2 }, BIG_BUT, BUTTOM_COLOR, State::Inactive, true);

    Button but1(window, Token::OK, { MSG_WIDTH / 3 - STANDARD_BUT._x / 2, MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 2 / 3 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 3 / 4 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text info(file_name, font, 20);

    temp1.Add(but1);
    temp1.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp1);
    inter.AddPanel(temp2);

    while (window->isOpen()) {
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
                    if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr) {
                        focus->SetState(State::Active);
                        focus->Draw();

                        mouse_pressed_on_button = true;
                    }

                    mouse_pressed = true;
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    inter.DrawFocus(focus);

                    if (mouse_pressed_on_button) {
                        switch (dynamic_cast<Button*>(focus)->GetToken()) {
                            case Token::OK:
                                window->close();
                                return file_name;
                            case Token::Cancel:
                                window->close();
                                break;
                            default:
                                break;
                        }
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
                        window->close();
                        return file_name;
                    }
                    else if (event.key.code == sf::Keyboard::Backspace && file_name.size() > 0) {
                        file_name.pop_back();
                    }
                    else if (file_name.size() < 20) {
                        char symbol = InfoManager::InpFromKey(event.key.code);

                        if (event.key.shift && symbol >= 97 && symbol <= 122) {
                            file_name += char(symbol - 32);
                        }
                        else if(symbol != -1) {
                            file_name += symbol;
                        }
                    }

                    info.setString(file_name);

                    sf::FloatRect area = info.getLocalBounds();
                    info.setOrigin(area.width / 2, area.height / 2 + info.getLineSpacing() + 5);
                    info.setPosition(sf::Vector2f(temp2.GetPosition()._x + temp2.GetWidth() / 2, temp2.GetPosition()._y + temp2.GetHeight() / 2));

                    break;
                }
                default:
                    break;
            }
        }

        window->draw(info);

        window->display();
        window->clear();
    }

    return std::string();
}

//----------------------------------------------------------------------------------------------------
//                                        Figures dialog
//----------------------------------------------------------------------------------------------------

Shape* Dialog::OpenFiguresDialog(Factory* fac) {
    Shape* shape = nullptr;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MSG_HEIGHT, MSG_WIDTH), "LAB_3", WINDOW);
    window->setFramerateLimit(60);

    sf::Event event;
    bool mouse_pressed = false, mouse_pressed_on_button = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, { 0, 0 }, { MSG_HEIGHT, MSG_WIDTH }, PANEL_COLOR, State::Inactive);

    Button but1(window, Token::circ, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but2(window, Token::rect, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 2 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but3(window, Token::triang, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 3 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but4(window, Token::unit, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2, MSG_WIDTH * 4 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but5(window, Token::Cancel, { MSG_HEIGHT / 2 - STANDARD_BUT._x / 2 , MSG_WIDTH * 5 / 6 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);
    temp.Add(but3);
    temp.Add(but4);
    temp.Add(but5);

    inter.SetWindow(window);
    inter.AddPanel(temp);

    while (window->isOpen()) {
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
                    if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr) {
                        focus->SetState(State::Active);
                        focus->Draw();

                        mouse_pressed_on_button = true;
                    }

                    mouse_pressed = true;
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    inter.DrawFocus(focus);

                    if (mouse_pressed_on_button) {
                        switch (dynamic_cast<Button*>(focus)->GetToken()) {
                            case Token::Cancel:
                                break;
                            default:
                                shape = fac->MakeShape(dynamic_cast<Button*>(focus)->GetToken());
                        }

                        window->close();
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
                    break;
                }
                default:
                    break;
            }
        }

        window->display();
        window->clear();
    }

    return shape;
}

//----------------------------------------------------------------------------------------------------
//                                        Color dialog
//----------------------------------------------------------------------------------------------------

sf::Color Dialog::OpenColorDialog() {
    int index = 0;
    std::string info[3];

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text[3];
    
    for (auto i = 0; i < 3; i++) {
        text[i].setFont(font);
        text[i].setCharacterSize(20);
    }

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "LAB_3", WINDOW);
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    sf::Event event;
    bool mouse_pressed = false;
    bool mouse_pressed_on_button = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, { 0, 0 }, { MSG_WIDTH, MSG_HEIGHT }, PANEL_COLOR, State::Inactive);

    Panel temp1(window, { MSG_WIDTH / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Panel temp2(window, { MSG_WIDTH * 2 / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Panel temp3(window, { MSG_WIDTH * 3 / 4 - STANDARD_BUT._x / 2, MSG_HEIGHT / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    Button but1(window, Token::OK, { MSG_WIDTH / 3 - STANDARD_BUT._x / 2, MSG_HEIGHT * 2 / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 2 / 3 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 2 / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp);
    inter.AddPanel(temp1);
    inter.AddPanel(temp2);
    inter.AddPanel(temp3);

    while (window->isOpen()) {
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
                    if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr) {
                        focus->SetState(State::Active);
                        focus->Draw();

                        mouse_pressed_on_button = true;
                    }

                    mouse_pressed = true;
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    inter.DrawFocus(focus);

                    if (mouse_pressed_on_button) {
                        switch (dynamic_cast<Button*>(focus)->GetToken()) {
                            case Token::OK:
                                window->close();
                                return sf::Color(InfoManager::ToNumber<int>(info[0]) % 256, InfoManager::ToNumber<int>(info[1]) % 256, InfoManager::ToNumber<int>(info[2]) % 256);
                            case Token::Cancel:
                                window->close();
                                break;
                            default:
                                break;
                        }
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
                        if (index == 2) {
                            window->close();
                            return sf::Color(InfoManager::ToNumber<int>(info[0]) % 256, InfoManager::ToNumber<int>(info[1]) % 256, InfoManager::ToNumber<int>(info[2]) % 256);
                        }
                        else {
                            index++;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Backspace) {
                        if (info[index].size() > 0) {
                            info[index].pop_back();
                        }
                        else if (info[index].size() == 0 && index > 0) {
                            index--;
                            info[index].pop_back();
                        }
                    }
                    else {
                        char symbol = InfoManager::InpFromKey(event.key.code);

                        if (symbol == 48 && info[index].size() == 0) {
                            info[index] += symbol;
                            text[index].setString(info[index]);
                            index++;
                        }
                        else if(symbol >= 48 && symbol <= 57) {
                            info[index] += symbol;
                        }

                        if (info[index].size() > 3 && index == 2) {
                            info[index].pop_back();
                        }

                        text[index].setString(info[index]);
                    }

                    if (info[index].size() == 3 && index < 2) {
                        index++;
                    }

                    for (auto i = 0; i < 3; i++) {
                        sf::FloatRect area = text[i].getLocalBounds();
                        text[i].setOrigin(area.width / 2, area.height / 2 + text[i].getLineSpacing() + 5);
                    }

                    text[0].setPosition(sf::Vector2f(temp1.GetPosition()._x + temp1.GetWidth() / 2, temp1.GetPosition()._y + temp1.GetHeight() / 2));
                    text[1].setPosition(sf::Vector2f(temp2.GetPosition()._x + temp2.GetWidth() / 2, temp2.GetPosition()._y + temp2.GetHeight() / 2));
                    text[2].setPosition(sf::Vector2f(temp3.GetPosition()._x + temp3.GetWidth() / 2, temp3.GetPosition()._y + temp3.GetHeight() / 2));

                    break;
                }
                default:
                    break;
            }
        }

        for (auto i = 0; i < 3; i++) {
            window->draw(text[i]);
        }

        window->display();
        window->clear();
    }

    return sf::Color(0, 0, 0, 0);
}

//----------------------------------------------------------------------------------------------------
//                                        Scale dialog
//----------------------------------------------------------------------------------------------------

Position Dialog::OpenScaleDialog() {
    int index = 0;
    std::string info[2];

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text[2];

    for (auto i = 0; i < 2; i++) {
        text[i].setFont(font);
        text[i].setCharacterSize(20);
    }

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MSG_WIDTH, MSG_HEIGHT), "LAB_3", WINDOW);
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    sf::Event event;
    bool mouse_pressed = false, mouse_pressed_on_button = false;

    Interface inter;

    sf::Vector2i cursor;

    Form* focus = nullptr;

    Panel temp(window, { 0, 0 }, { MSG_WIDTH, MSG_HEIGHT }, PANEL_COLOR, State::Inactive);

    Panel temp1(window, { MSG_WIDTH / 3 - STANDARD_BUT._x / 2, MSG_HEIGHT / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Panel temp2(window, { MSG_WIDTH * 2 / 3 - STANDARD_BUT._x / 2, MSG_HEIGHT / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    Button but1(window, Token::OK, { MSG_WIDTH / 3 - STANDARD_BUT._x / 2, MSG_HEIGHT * 2 / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);
    Button but2(window, Token::Cancel, { MSG_WIDTH * 2 / 3 - STANDARD_BUT._x / 2 , MSG_HEIGHT * 2 / 3 - STANDARD_BUT._y / 2 }, STANDARD_BUT, BUTTOM_COLOR, State::Inactive, true);

    temp.Add(but1);
    temp.Add(but2);

    inter.SetWindow(window);
    inter.AddPanel(temp);
    inter.AddPanel(temp1);
    inter.AddPanel(temp2);

    while (window->isOpen()) {
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
                    if (event.mouseButton.button == sf::Mouse::Left && focus != nullptr) {
                        focus->SetState(State::Active);
                        focus->Draw();

                        mouse_pressed_on_button = true;
                    }

                    mouse_pressed = true;
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    inter.DrawFocus(focus);

                    if (mouse_pressed_on_button) {
                        switch (dynamic_cast<Button*>(focus)->GetToken()) {
                            case Token::OK:
                                window->close();
                                return Position(InfoManager::ToNumber<float>(info[0]), InfoManager::ToNumber<float>(info[1]));
                            case Token::Cancel:
                                window->close();
                                break;
                            default:
                                break;
                        }
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
                        if (index == 1) {
                            window->close();
                            return Position(InfoManager::ToNumber<float>(info[0]), InfoManager::ToNumber<float>(info[1]));
                        }
                        else {
                            index++;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Backspace) {
                        if (info[index].size() > 0) {
                            info[index].pop_back();
                            text[index].setString(info[index]);
                        }
                        else if (info[index].size() == 0 && index > 0) {
                            index--;
                            info[index].pop_back();
                            text[index].setString(info[index]);
                        }
                    }
                    else {
                        char symbol = InfoManager::InpFromKey(event.key.code);

                        if (symbol == 48 && info[index].size() == 0) {
                            info[index] += symbol;
                            text[index].setString(info[index]);
                            index++;
                        }
                        else if ((symbol >= 48 && symbol <= 57)) {
                            info[index] += symbol;
                        }
                        else if (symbol == '.') {
                            info[index] += symbol;
                        }

                        if (info[index].size() > 4 && index == 1) {
                            info[index].pop_back();
                        }

                        text[index].setString(info[index]);
                    }

                    if (info[index].size() == 4 && index < 1) {
                        index++;
                    }

                    for (auto i = 0; i < 2; i++) {
                        sf::FloatRect area = text[i].getLocalBounds();
                        text[i].setOrigin(area.width / 2, area.height / 2 + text[i].getLineSpacing() + 5);
                    }

                    text[0].setPosition(sf::Vector2f(temp1.GetPosition()._x + temp1.GetWidth() / 2, temp1.GetPosition()._y + temp1.GetHeight() / 2));
                    text[1].setPosition(sf::Vector2f(temp2.GetPosition()._x + temp2.GetWidth() / 2, temp2.GetPosition()._y + temp2.GetHeight() / 2));

                    break;
                }
                default:
                    break;
            }
        }

        for (auto i = 0; i < 2; i++) {
            window->draw(text[i]);
        }

        window->display();
        window->clear();
    }

    return Position(1, 1);
}