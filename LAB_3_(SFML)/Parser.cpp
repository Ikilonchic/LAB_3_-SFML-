#include "Parser.hpp"

std::vector<std::string> Parser::Dispenser(std::string line)
{
	std::vector<std::string> words;
	std::istringstream ist(line);
	std::string tmp;

	while (ist >> tmp)
	{
		if (tmp != "|" || tmp != "+")
		{
			words.push_back(tmp);
		}
	}

	return words;
}

std::string Parser::ToStr(int number)
{
	return std::to_string(number);
}

int Parser::ToInt(std::string number)
{
	int result;
	std::istringstream ist(number);

	ist >> result;

	return result;
}

std::string Parser::SaveFigure(Shape* a)
{
	std::string line;

	line = "| " + a->_name + " | " + ToStr(a->_pos._x) + " | " + ToStr(a->_pos._y) + " | ";

	if (a->_name == "rect")
	{
		line += ToStr(a->_size._x) + " " + ToStr(a->_size._y) + " | ";
	}
	else
	{
		line += ToStr(a->_size._x) + " | ";
	}

	line += ToStr(a->_color.r) + " | " + ToStr(a->_color.g) + " | " + ToStr(a->_color.b) + " | " + ToStr(a->_angle) + " |";

	return line;
}

////////////////////////////////////////////////////////////
std::vector<Shape*> Parser::ReadFromFile(std::string name_f)
{
	std::vector<Shape*> figures;
	std::vector<Shape*> unit;

	std::ifstream file(name_f + ".txt");

	std::string line;
	std::vector<std::string> parameters;

	while (std::getline(file, line))
	{
		
	}

	return std::vector<Shape*>();
}

void Parser::SaveToFile(std::string name_f, std::vector<Shape*> figures)
{
	std::ofstream file(name_f + ".txt");

	file << "#-------------------------------------------------------#" << std::endl;
	file << "# name | x   | y   | size     | r   | g   | b   | angle #" << std::endl;
	file << "#-------------------------------------------------------#" << std::endl;

	for (auto a : figures)
	{
		if (a->_name == "unit")
		{
			for (auto b : dynamic_cast<UnitShape*>(a)->GetShapes())
			{
				file << SaveFigure(b) << std::endl;
			}
		}
		else
		{
			file << SaveFigure(a) << std::endl;
		}

		file << "---------------------------------------------------------" << std::endl;
	}
}
