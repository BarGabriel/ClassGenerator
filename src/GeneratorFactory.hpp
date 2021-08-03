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
	std::unique_ptr<Generator> getGenerator(std::string generatorType) const;

private:

	void initGeneratorsMap();
	std::unique_ptr<Generator> cppGenerator() const;
	std::unique_ptr<Generator> pytonGenerator() const;

	std::unordered_map<std::string, std::function<std::unique_ptr<Generator>()>> _generatorsMap;
};

#endif