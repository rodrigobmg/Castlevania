#include <ctime>
#include "TimeHelper.h"

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

std::string TimeHelper::GetTimeNow(const char *format)
{
	std::time_t timeNow = std::time(nullptr);
	std::tm timeStruct = *std::localtime(&timeNow);
	char formattedTime[80];

	strftime(formattedTime, sizeof(formattedTime), format, &timeStruct);

	return formattedTime;
}