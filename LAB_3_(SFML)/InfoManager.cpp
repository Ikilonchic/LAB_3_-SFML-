#include "InfoManager.hpp"

std::vector<std::string> InfoManager::Dispenser(std::string line) {
	std::vector<std::string> words;
	std::istringstream ist(line);
	std::string tmp;

	while (ist >> tmp) {
		if (tmp != "|") {
			words.push_back(tmp);
		}
	}

	return words;
}

char InfoManager::InpFromKey(sf::Keyboard::Key key) {
	switch (key) {
        case sf::Keyboard::Unknown:
            return '\0';
            break;
        case sf::Keyboard::A:
            return 'a';
            break;
        case sf::Keyboard::B:
            return 'b';
            break;
        case sf::Keyboard::C:
            return 'c';
            break;
        case sf::Keyboard::D:
            return 'd';
            break;
        case sf::Keyboard::E:
            return 'e';
            break;
        case sf::Keyboard::F:
            return 'f';
            break;
        case sf::Keyboard::G:
            return 'g';
            break;
        case sf::Keyboard::H:
            return 'h';
            break;
        case sf::Keyboard::I:
            return 'i';
            break;
        case sf::Keyboard::J:
            return 'j';
            break;
        case sf::Keyboard::K:
            return 'k';
            break;
        case sf::Keyboard::L:
            return 'l';
            break;
        case sf::Keyboard::M:
            return 'm';
            break;
        case sf::Keyboard::N:
            return 'n';
            break;
        case sf::Keyboard::O:
            return 'o';
            break;
        case sf::Keyboard::P:
            return 'p';
            break;
        case sf::Keyboard::Q:
            return 'q';
            break;
        case sf::Keyboard::R:
            return 'r';
            break;
        case sf::Keyboard::S:
            return 's';
            break;
        case sf::Keyboard::T:
            return 't';
            break;
        case sf::Keyboard::U:
            return 'u';
            break;
        case sf::Keyboard::V:
            return 'v';
            break;
        case sf::Keyboard::W:
            return 'w';
            break;
        case sf::Keyboard::X:
            return 'x';
            break;
        case sf::Keyboard::Y:
            return 'y';
            break;
        case sf::Keyboard::Z:
            return 'z';
            break;
        case sf::Keyboard::Num0:
            return '0';
            break;
        case sf::Keyboard::Num1:
            return '1';
            break;
        case sf::Keyboard::Num2:
            return '2';
            break;
        case sf::Keyboard::Num3:
            return '3';
            break;
        case sf::Keyboard::Num4:
            return '4';
            break;
        case sf::Keyboard::Num5:
            return '5';
            break;
        case sf::Keyboard::Num6:
            return '6';
            break;
        case sf::Keyboard::Num7:
            return '7';
            break;
        case sf::Keyboard::Num8:
            return '8';
            break;
        case sf::Keyboard::Num9:
            return '9';
            break;
        case sf::Keyboard::Space:
            return ' ';
            break;
        case sf::Keyboard::Enter:
            return '\n';
            break;
        case sf::Keyboard::Tab:
            return '\t';
            break;
        case sf::Keyboard::Numpad0:
            return '0';
            break;
        case sf::Keyboard::Numpad1:
            return '1';
            break;
        case sf::Keyboard::Numpad2:
            return '2';
            break;
        case sf::Keyboard::Numpad3:
            return '3';
            break;
        case sf::Keyboard::Numpad4:
            return '4';
            break;
        case sf::Keyboard::Numpad5:
            return '5';
            break;
        case sf::Keyboard::Numpad6:
            return '6';
            break;
        case sf::Keyboard::Numpad7:
            return '7';
            break;
        case sf::Keyboard::Numpad8:
            return '8';
            break;
        case sf::Keyboard::Numpad9:
            return '9';
            break;
        case sf::Keyboard::Period:
            return '.';
            break;
        default:
            return -1;
            break;
	}
}

std::string InfoManager::ToStr(int number) {
	return std::to_string(number);
}

void InfoManager::InsToStr(std::string& line, std::string ins, int index) {
	for (auto i = 0; i < ins.length(); i++, index++) {
		line[index] = ins[i];
	}
}

std::string InfoManager::SaveFigure(Shape* a) {
	std::string line = "|      |      |      |           |     |     |     |       |       |";

	InsToStr(line, a->_name, 2);
	InsToStr(line, ToStr(a->_pos._x), 9);
	InsToStr(line, ToStr(a->_pos._y), 16);
	InsToStr(line, ToStr(a->_size._x), 23);

	if (a->_name == "rect") {
		InsToStr(line, ToStr(a->_size._y), 28);
	}

	InsToStr(line, ToStr(a->_color.r), 35);
	InsToStr(line, ToStr(a->_color.g), 41);
	InsToStr(line, ToStr(a->_color.b), 47);
	InsToStr(line, ToStr(a->_angle), 53);
	InsToStr(line, ToStr(a->_scale._x), 61);
	InsToStr(line, ToStr(a->_scale._y), 64);

	return line;
}

std::vector<Shape*> InfoManager::ReadFromFile(std::string name_f) {
	std::vector<Shape*> figures;
	std::vector<Shape*> unit;

	std::ifstream file(name_f + ".txt");

	std::string line;
	std::vector<std::string> parameters;

	while (std::getline(file, line)) {
		if (line[0] == '#') {
			continue;
		}
		else if (line[0] == '+') {
			if (unit.size() == 1 && unit[0]->OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) {
				figures.push_back(unit[0]);
			}
			else if (unit.size() > 1 && UnitShape(std::shared_ptr<sf::RenderWindow>(), unit).OnArea(SC_WIDTH * 3 / 4, SC_HEIGHT)) {
				figures.push_back(new UnitShape(std::shared_ptr<sf::RenderWindow>(), unit));
			}

			unit.clear();
			continue;
		}

		parameters = Dispenser(line);

		if (parameters[0] == "rect") {
			unit.push_back(new Rectangle(std::shared_ptr<sf::RenderWindow>(), { ToNumber<float>(parameters[1]), ToNumber<float>(parameters[2]) }, { ToNumber<float>(parameters[3]), ToNumber<float>(parameters[4]) }, sf::Color(ToNumber<float>(parameters[5]), ToNumber<float>(parameters[6]), ToNumber<float>(parameters[7])), ToNumber<float>(parameters[8]), { ToNumber<float>(parameters[9]), ToNumber<float>(parameters[10]) }));
		}
		else if (parameters[0] == "circ") {
			unit.push_back(new Circle(std::shared_ptr<sf::RenderWindow>(), { ToNumber<float>(parameters[1]), ToNumber<float>(parameters[2]) }, ToNumber<float>(parameters[3]), sf::Color(ToNumber<float>(parameters[4]), ToNumber<float>(parameters[5]), ToNumber<float>(parameters[6])), ToNumber<float>(parameters[7]), { ToNumber<float>(parameters[8]), ToNumber<float>(parameters[9]) }));
		}
		else if (parameters[0] == "tria") {
			unit.push_back(new Triangle(std::shared_ptr<sf::RenderWindow>(), { ToNumber<float>(parameters[1]), ToNumber<float>(parameters[2]) }, ToNumber<float>(parameters[3]), sf::Color(ToNumber<float>(parameters[4]), ToNumber<float>(parameters[5]), ToNumber<float>(parameters[6])), ToNumber<float>(parameters[7]), { ToNumber<float>(parameters[8]), ToNumber<float>(parameters[9]) }));
		}
	}

	return figures;
}

void InfoManager::SaveToFile(std::string name_f, std::vector<Shape*> figures) {
	std::ofstream file(name_f + ".txt");

	file << "#------------------------------------------------------------------#" << std::endl;
	file << "# name | x    | y    | size      | r   | g   | b   | angle | scale #" << std::endl;
	file << "#------------------------------------------------------------------#" << std::endl;

	for (auto a : figures) {
		if (a->_name == "unit") {
			for (auto b : dynamic_cast<UnitShape*>(a)->GetShapes()) {
				file << SaveFigure(b) << std::endl;
			}
		}
		else {
			file << SaveFigure(a) << std::endl;
		}

		file << "+------------------------------------------------------------------+" << std::endl;
	}
}
