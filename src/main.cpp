//============================================================================
// Name        : Gpp.cpp
// Author      : Lemmy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <locale>
#include <sstream>
#include <boost/locale/encoding_utf.hpp>
#include <boost/locale.hpp>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/variant.hpp>
#include <boost/program_options.hpp>
#include <sparge/gold/file.hpp>
#include <sparge/gold/to_core.hpp>
#include <sparge/generator.hpp>

namespace po = boost::program_options;


int main(int argc, char ** argv)
{
	po::options_description desc("Possible options");

	desc.add_options()
	    ("help", "produce help message")
	    ("input",     po::value<std::string>(), "set input file")
		("namespace", po::value<std::string>(), "set the namespace for the output")
		("output", 	  po::value<std::string>(), "output directory")
		("no-parser",    "generate no parser")
		("no-tokenizer", "generate no tokenizer")
		("no-listener",  "generate no listener")
		("language-name","override language name")
		("doxygen",  po::value<std::string>(), "generate doxygen documentation")
		("print-input-data", "Print the input data, depending on the format")
		("dfa-graphviz",  po::value<std::string>(), "produce a graphviz image for the dfa state machine")
		("lalr-graphviz", po::value<std::string>(), "produce a graphviz image for the lalr state machine")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.empty() || vm.count("help"))
	{
	    std::cout << desc << "\n";
	    return 1;
	}


	if (vm.count("input") == 0)
	{
		std::cerr << "No input file defined";
		return 1;
	}

	auto f = sparge::gold::read_raw_file(vm["input"].as<std::string>());

	if (vm.count("print-input-data"))
		std::cout << f << std::endl;

	auto d = sparge::gold::to_core(f);

	if (vm.count("dfa-graphviz"))
	{
		std::ofstream of(vm["dfa-graphviz"].as<std::string>());

		d.plot_dfa(of);
	}

	sparge::generator g;
	g.data = sparge::gold::to_core(f);

	if (vm.count("output"))
		g.set_path(vm["output"].as<std::string>());

	if (vm.count("namespace"))
		g.set_name_space(vm["namespace"].as<std::string>());


	g.write_symbols();
	g.write_dfa_states();
	g.write_char_set();

	return 0;
}
