#include "src/GeneratorFactory.hpp"
#include "src/Options.hpp"

int main(int argc, char** argv)
{
	Options options(argc, argv);
	auto result = options.parse();

	std::string lang = result[Options::LANG_OPTION].as<std::string>();
	std::string name = result[Options::NAME_OPTION].as<std::string>();

	GeneratorFactory generatorFactory;
	std::unique_ptr<Generator> generator = generatorFactory.getGenerator(std::move(lang));

	generator->setClassName(std::move(name));

	if (result.count(Options::PRIVATE_OPTION))
	{
		auto privateMembers = result[Options::PRIVATE_OPTION].as<std::vector<std::string>>();
		generator->validatePrivateMembers(privateMembers);
		generator->setPrivateMembers(privateMembers);
	}

	generator->generate();

	return 1;
}