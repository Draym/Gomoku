#pragma once

#include <vector>
#include "map\Grid.hpp"
#include "AI\AI.hpp"

class IAManager
{
public:
	static void init();
	static std::vector<std::string> getMethodsId();
	static IAI<Grid<Cell>>::Function getMethod(std::string id);
private:
	static std::vector<std::pair<std::string, IAI<Grid<Cell>>::Function>>	iaMethods;
};

