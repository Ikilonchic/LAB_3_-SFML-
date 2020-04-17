#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "ShapeFactory.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Parser
//----------------------------------------------------------------------------------------------------

class Parser final
{
private:
	static std::vector<std::string> Dispenser(std::string line);
	static std::string ToStr(int number);
	static int ToInt(std::string number);
	static std::string SaveFigure(Shape* a);

public:
	static std::vector<Shape*> ReadFromFile(std::string name_f);
	static void SaveToFile(std::string name_f, std::vector<Shape*> figures);
};

#endif