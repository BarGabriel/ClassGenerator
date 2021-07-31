#include "GeneratorFactory.hpp"

#include "CppGenerator.hpp"
#include "PythonGenerator.hpp"

GeneratorFactory::GeneratorFactory()
{
	initGeneratorsMap();
}

std::unique_ptr<Generator> GeneratorFactory::getGenerator(const std::string& generatorType)
{
	auto it = _generatorsMap.find(generatorType);
	if (it != _generatorsMap.end())
	{
		return it->second();
	}
	else
	{
		std::cerr << "Invalid generator type..\nMake sure the lang option is valid.";
		exit(0);
	}
}

void GeneratorFactory::initGeneratorsMap()
{
	_generatorsMap.emplace(std::pair<std::string, std::function<std::unique_ptr<Generator>()>>("c++", std::bind(&GeneratorFactory::cppGenerator, this)));
	_generatorsMap.emplace(std::pair<std::string, std::function<std::unique_ptr<Generator>()>>("cpp", std::bind(&GeneratorFactory::cppGenerator, this)));
	_generatorsMap.emplace(std::pair<std::string, std::function<std::unique_ptr<Generator>()>>("python", std::bind(&GeneratorFactory::pytonGenerator, this)));
}

std::unique_ptr<Generator> GeneratorFactory::cppGenerator()
{
	return std::make_unique<CppGenerator>();
}

std::unique_ptr<Generator> GeneratorFactory::pytonGenerator()
{
	return std::make_unique<PythonGenerator>();
}

