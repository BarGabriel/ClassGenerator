#include "Options.hpp"

Options::Options(int argc, char** argv) : _argc(argc), _argv(argv), _options(APP_NAME, DESCRIPTION)
{
	_options.add_options()
		(HELP_OPTION, "Print usage")
		(LANG_OPTION, "langueage", cxxopts::value<std::string>())
		(NAME_OPTION, "Class name", cxxopts::value<std::string>())
		(PRIVATE_OPTION, "private members", cxxopts::value<std::vector<std::string>>());
}

cxxopts::ParseResult Options::parse()
{
	auto result = _options.parse(_argc, _argv);
	validateArgs(result);
	return result;
}

void Options::validateArgs(cxxopts::ParseResult result)
{
	if (result.count(HELP_OPTION))
	{
		std::cout << _options.help() << std::endl;
		exit(0);
	}

	if (!result.count(LANG_OPTION))
	{
		std::cout << "Please enter the language." << std::endl;
		exit(0);
	}

	if (!result.count(NAME_OPTION))
	{
		std::cout << "Please enter the class name." << std::endl;
		exit(0);
	}
}
