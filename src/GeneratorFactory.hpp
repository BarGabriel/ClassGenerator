#ifndef GENERATORFACTORY_HPP
#define GENERATORFACTORY_HPP

#include "Generator.hpp"
#include <unordered_map>
#include <functional>
#include <memory>

class GeneratorFactory
{
public:
	GeneratorFactory();
	std::unique_ptr<Generator> getGenerator(const std::string& generatorType);

private:

	void initGeneratorsMap();

	std::unique_ptr<Generator> cppGenerator();
	std::unique_ptr<Generator> pytonGenerator();

	std::unordered_map<std::string, std::function<std::unique_ptr<Generator>()>> _generatorsMap;

};





#endif