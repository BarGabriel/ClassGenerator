#ifndef PythonGenerator_HPP
#define PythonGenerator_HPP

#include "Generator.hpp"

class PythonGenerator : public Generator
{
public:

	~PythonGenerator () = default;

	void generate() override;

private:

	std::string generateConstructor() const override;
	std::string generateSet(const std::string& memberName, const std::string& returnType = "") const override;
	std::string generateGet(const std::string& memberName, const std::string& returnType = "") const override;
};

#endif