#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include "cxxopts.hpp"


class Options
{
public:

	static constexpr auto HELP_OPTION = "help";
	static constexpr auto LANG_OPTION = "lang";
	static constexpr auto NAME_OPTION = "name";
	static constexpr auto PRIVATE_OPTION = "private";

	Options(int argc, char** argv);
	cxxopts::ParseResult parse();

private:

	static constexpr auto APP_NAME = "Class Generator";
	static constexpr auto DESCRIPTION = "A program for generate classes in different langueages";		

	void validateArgs(cxxopts::ParseResult result);

	int _argc;
	char** _argv;
	cxxopts::Options _options;
};

#endif
