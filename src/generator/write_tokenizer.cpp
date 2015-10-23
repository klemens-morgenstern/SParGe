/**
 * @file   write_tokenizer.cpp
 * @date   21.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#include <sparge/generator.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale/encoding.hpp>

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

namespace sparge
{

std::vector<std::string> get_case(const std::vector<char32_t> &char_set)
{
	static boost::format f("\tcase %i1%:\n");

	std::vector<std::string> vec;

	return vec;
}


void generator::write_tokenizer() const
{

	auto out = path / "tokenizer.hpp";

    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "TOKENIZER_H_");

    ofs << "#include <" << path.string() << "/symbols.hpp" << ">\n\n";
    ofs << ns_in;


    ofs << ns_out;
    ofs << "\n\n#endif\n";
}
}
