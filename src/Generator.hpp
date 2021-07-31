
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include <vector>

class Generator
{
public:

	Generator();
	void setClassName(const std::string& name);
	void setPrivateMembers(std::vector<std::string> members);
	virtual void generate() = 0;

protected:

	virtual std::string generateConstructor() const = 0;
	virtual std::string generateSet(const std::string& memberName, const std::string& returnType = "") const = 0;
	virtual std::string generateGet(const std::string& memberName, const std::string& returnType = "") const = 0;

	std::string _className;
	std::vector<std::string> _privateMembers;
};










#endif // !1
