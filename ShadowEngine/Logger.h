#pragma once
class Logger
{
public:
	Logger();
	~Logger();

	static void dprint(std::list<std::string> strList, std::string separator=", ", bool separateFirst=false);
};

