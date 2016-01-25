#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Graphic\ResourceManager.h"

class ConvertTools
{
public:
	static bool			convertToBool(std::string value);
	static EColor		convertToColor(std::string value);
	static std::string	convert(std::vector<std::string> values);
};

