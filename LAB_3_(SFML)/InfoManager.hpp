#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "Factory.hpp"

//----------------------------------------------------------------------------------------------------
//                                        Parser
//----------------------------------------------------------------------------------------------------

class InfoManager final
{
private:
	static std::vector<std::string> Dispenser(std::string line);

	static std::string ToStr(int number);
	static void InsToStr(std::string& line, std::string ins, int index = 0);

	// Save shape to line //
	static std::string SaveFigure(std::unique_ptr<Shape> a);

public:
	// Ñonversion to char //
	static char InpFromKey(sf::Keyboard::Key key);

	// Conversion to number //
	template<class T>
	static T ToNumber(std::string number) {
		T result;
		std::istringstream ist(number);

		ist >> result;
		return result;
	}

	// Read and save to file //
	static std::vector<std::unique_ptr<Shape>> ReadFromFile(std::string name_f);
	static void SaveToFile(std::string name_f, std::vector<std::unique_ptr<Shape>> figures);
};

#endif