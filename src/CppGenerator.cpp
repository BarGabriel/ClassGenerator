#include "CppGenerator.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>

CppGenerator::CppGenerator()
{
	initTypes();
}

void CppGenerator::generate()
{
	generateHeader();
	generateSource();
}

void CppGenerator::initTypes()
{
	_types.emplace(std::pair<std::string, std::string>("s", "std::string"));
	_types.emplace(std::pair<std::string, std::string>("i", "int"));
	_types.emplace(std::pair<std::string, std::string>("d", "double"));
}

void CppGenerator::validatePrivateMembers(std::vector<std::string> members) const
{
	Generator::validatePrivateMembers(members);
	if (members.size() % 2)
	{
		std::cerr << "Invalid private members" << std::endl;
		exit(0);
	}
	for (auto it = members.cbegin(); it != members.cend(); it += 2)
	{
		if (*it != STRING_TYPE && *it != INTEGER_TYPE)
		{
			std::cerr << "Invalid type. type: " << *it << std::endl;
			exit(0);
		}
	}
}

void CppGenerator::generateHeader() const
{
	std::ofstream headerFile;
	headerFile.open(_className + ".hpp");
	std::string upperClassName = _className;
	std::transform(upperClassName.begin(), upperClassName.end(), upperClassName.begin(), ::toupper);
	headerFile << "#ifndef " + upperClassName + "_HPP\n";
	headerFile << "#define " + upperClassName + "_HPP\n\n";

	headerFile << "#include <iostream>\n\n";

	headerFile << "class " + _className + "\n";
	headerFile << "{\n";

	headerFile << "public:\n";

	if (_privateMembers.empty())
	{
		headerFile << "\t" + _className + "();\n\n";
	}
	else
	{
		headerFile << "\t" + _className + "(";

		std::string membersType, memberName;
		auto membersIt = _privateMembers.cbegin();
		while (membersIt != _privateMembers.cend())
		{
			membersType = getType(*membersIt++);
			memberName = *membersIt++;
			headerFile << membersType + SPACE + memberName;
			if (membersIt != _privateMembers.cend())
			{
				headerFile << ", ";
			}
		}
		headerFile << ");\n\n";


		// Declare getters & setters for privete members
		membersIt = _privateMembers.cbegin();
		while (membersIt != _privateMembers.cend())
		{
			membersType = getType(*membersIt++);
			memberName = *membersIt++;
			headerFile << "\t" + std::string("void set_") + memberName + "(" + membersType + " value);\n";
			headerFile << "\t" + membersType + " get_" + memberName + "() const;\n\n";
		}


		// Declare private members
		headerFile << "\nprivate:\n";
		membersIt = _privateMembers.cbegin();
		while (membersIt != _privateMembers.cend())
		{
			membersType = getType(*membersIt++);
			memberName = *membersIt++;
			headerFile << "\t" + membersType + SPACE + "_" + memberName + ";\n";
		}
	}

	headerFile << "};\n\n";
	headerFile << "#endif\n";

	headerFile.close();
}

void CppGenerator::generateSource() const
{
	std::ofstream sourceFile;
	sourceFile.open(_className + ".cpp");
	sourceFile << "#include " + std::string("\"") + _className + ".hpp" + "\"" + "\n\n";

	sourceFile << generateConstructor();
	if (!_privateMembers.empty())
	{
		// Getters & Setters
		std::string memberType, memberName;
		auto membersIt = _privateMembers.cbegin();
		while (membersIt != _privateMembers.cend())
		{
			memberType = getType(*membersIt++);
			memberName = *membersIt++;

			sourceFile << generateSet(memberName, memberType);
			sourceFile << generateGet(memberName, memberType);
		}
	}

	sourceFile.close();
}

std::string CppGenerator::getType(const std::string& memberType) const
{
	return _types.find(memberType)->second;
}

std::string CppGenerator::generateConstructor() const
{
	std::stringstream constructor;
	constructor << _className + "::" + _className + "(";
	if (_privateMembers.empty())
	{
		constructor << ")\n{\n\n}\n\n";
	}
	else
	{
		std::string memberType, memberName;
		auto membersIt = _privateMembers.begin();
		while (membersIt != _privateMembers.end())
		{
			memberType = getType(*membersIt++);
			memberName = *membersIt++;

			constructor << memberType + SPACE + memberName;
			if (membersIt != _privateMembers.end())
			{
				constructor << ", ";
			}
		}

		constructor << ")\n{\n";

		membersIt = _privateMembers.begin();
		while (membersIt != _privateMembers.end())
		{
			memberType = getType(*membersIt++);
			memberName = *membersIt++;

			constructor << "\t_" + memberName + " = " + memberName + ";\n";
		}
		constructor << "}\n\n";
	}

	return constructor.str();
}

std::string CppGenerator::generateSet(const std::string& memberName, const std::string& returnType) const
{
	std::stringstream setFunc;
	setFunc << "void " + _className + "::set_" + memberName + "(" + returnType + " value" + ")\n{\n";
	setFunc << "\t_" + memberName + " = " + "value;\n}\n\n";
	return setFunc.str();
}

std::string CppGenerator::generateGet(const std::string& memberName, const std::string& returnType) const
{
	std::stringstream getFunc;
	getFunc << returnType + SPACE + _className + "::get_" + memberName + "() const\n{\n";
	getFunc << "\treturn _" + memberName + ";\n}\n\n";
	return getFunc.str();
}