#include "pch.h"


Logger::Logger()
{
}


Logger::~Logger()
{
}


void Logger::dprint(std::list<std::string> strList, std::string separator, bool separateFirst) {
	bool isFirst = true;
	auto iter = strList.begin();

	while (iter != strList.end()) {
		OutputDebugStringA(((*iter)).c_str());

		if (++iter != strList.end() && (separateFirst || !isFirst)) {
			OutputDebugStringA(((separator)).c_str());
		}
		isFirst = false;
	}
	OutputDebugStringA("\n");
}