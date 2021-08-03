#include "PythonGenerator.hpp"

#include <fstream>
#include <sstream>

void PythonGenerator::generate()
{
	std::ofstream file;
	file.open(_className + ".py");
	file << "class " + _className + ":\n";
	file << generateConstructor();

	if (!_privateMembers.empty())
	{
		std::string memberName;

		// Getters & Setters
		for (size_t i = 0; i < _privateMembers.size(); ++i)
		{
			memberName = _privateMembers.at(i);
			file << generateSet(memberName);
			file << generateGet(memberName);
		}
	}

	file.close();
}

std::string PythonGenerator::generateConstructor() const
{
	std::stringstream constructor;
	if (_privateMembers.empty())
	{
		constructor << "   def __init__(self):\n";
		constructor << "      pass";
	}
	else
	{
		std::string memberName;

		// Constructor
		constructor << "   def __init__(self";
		for (size_t i = 0; i < _privateMembers.size(); ++i)
		{
			memberName = _privateMembers.at(i);
			constructor << ", " + memberName;
		}
		constructor << "):\n";

		// Constructor implementation
		for (size_t i = 0; i < _privateMembers.size(); ++i)
		{
			memberName = _privateMembers.at(i);
			constructor << "      self._" + memberName + " = " + memberName + "\n";
		}
		constructor << "\n";
	}

	return constructor.str();
}

std::string PythonGenerator::generateSet(const std::string& memberName, const std::string& returnType) const
{
	std::stringstream setFunc;
	setFunc << "   def set_" << memberName << "(self, value):\n";
	setFunc << "      self._" << memberName << " = value\n\n";
	return setFunc.str();
}

std::string PythonGenerator::generateGet(const std::string& memberName, const std::string& returnType) const
{
	std::stringstream getFunc;
	getFunc << "   def get_" << memberName << "(self):\n";
	getFunc << "      return self._" << memberName << "\n\n";
	return getFunc.str();
}