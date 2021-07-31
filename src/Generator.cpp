#include "Generator.hpp"



Generator::Generator()
{
}

void Generator::setClassName(const std::string& name)
{
	_className = name;
}

void Generator::setPrivateMembers(std::vector<std::string> members)
{
	_privateMembers = members;
}



