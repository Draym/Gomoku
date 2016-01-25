#include "Utils\ConvertTools.h"

bool	ConvertTools::convertToBool(std::string value) {
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (value == "true")
		return true;
	else
		return false;
}

EColor	ConvertTools::convertToColor(std::string value) {
	static const std::string colorStrings[3] = { "black", "green", "red" };

	for (std::size_t i = 0; i < 3; ++i) {
		if (value == colorStrings[i])
			return static_cast<EColor>(i);
	}
	return EColor::BLACK;
}

std::string		ConvertTools::convert(std::vector<std::string> values)
{
	std::string	result;

	for (std::size_t i = 0; i < values.size(); ++i)
	{
		result += "[" + values[i] + "] ";
	}
	return result;
}