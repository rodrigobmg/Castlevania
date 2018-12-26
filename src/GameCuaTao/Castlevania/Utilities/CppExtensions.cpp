#include <algorithm>
#include "CppExtensions.h"

bool Castlevania::ToBoolean(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	auto isstream = std::istringstream{ str };
	auto result = bool{};

	isstream >> std::boolalpha >> result;

	return result;
}

bool Castlevania::StartsWith(const std::string &str, const std::string &prefix)
{
	return str.length() >= prefix.length() && str.compare(0, prefix.length(), prefix) == 0;
}

bool Castlevania::EndsWith(const std::string &str, const std::string &suffix)
{
	return str.length() >= suffix.length() && str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::vector<std::string> Castlevania::Split(const std::string &str, char delimiter)
{
	auto sstream = std::stringstream{ str };
	auto subStr = std::string{};
	auto results = std::vector<std::string>{};

	while (std::getline(sstream, subStr, delimiter))
	{
		results.push_back(subStr);
	}
	
	return results;
}
