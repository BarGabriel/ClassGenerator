#include "Generator.hpp"

void Generator::setClassName(std::string name)
{
	_className = name;
}

void Generator::setPrivateMembers(std::vector<std::string> members)
{
	_privateMembers = members;
}

void Generator::validatePrivateMembers(std::vector<std::string> members) const
{
	if (members.empty()) 
	{
		std::cerr << "There are no private members" << std::endl;
		exit(0);
	}
}
