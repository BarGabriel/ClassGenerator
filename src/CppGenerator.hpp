
#ifndef CppGenerator_HPP
#define CppGenerator_HPP

#include "Generator.hpp"
#include <unordered_map>

class CppGenerator : public Generator
{
public:

	CppGenerator();
	~CppGenerator() = default;

	void generate() override;

private:

	static constexpr auto SPACE = " ";

	void initTypes();
	void generateHeader();
	void generateSource();
	std::string getType(const std::string& memberType) const;
	std::string generateConstructor() const override;
	std::string generateSet(const std::string& memberName, const std::string& returnType = "") const override;
	std::string generateGet(const std::string& memberName, const std::string& returnType = "") const override;

	std::unordered_map<std::string, std::string> _types;
};



#endif 