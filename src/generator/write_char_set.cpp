/**
 * @file   write_char_set.cpp
 * @date   23.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */


#include <sparge/generator.hpp>

namespace sparge
{

void generator::write_char_set() const
{
	std::string ecodings{
		"enum class encodings\n"
		"{\n"
		"\tcp1250,      \n"
		"\tcp1251,      \n"
		"\tcp1252,      \n"
		"\tcp1253,      \n"
		"\tcp1254,      \n"
		"\tcp1255,      \n"
		"\tcp1256,      \n"
		"\tcp1257,      \n"
		"\tcp874,       \n"
		"\tcp932,       \n"
		"\tcp936,       \n"
		"\teucjp,       \n"
		"\teuckr,       \n"
		"\tgb18030,     \n"
		"\tgb2312,      \n"
		"\tgbk,         \n"
		"\tiso2022jp,   \n"
		"\tiso2022kr,   \n"
		"\tiso88591,    \n"
		"\tiso88592,    \n"
		"\tiso88593,    \n"
		"\tiso88594,    \n"
		"\tiso88595,    \n"
		"\tiso88596,    \n"
		"\tiso88597,    \n"
		"\tiso88598,    \n"
		"\tiso88599,    \n"
		"\tiso885910,   \n"
		"\tiso885911,   \n"
		"\tiso885912,   \n"
		"\tiso885913,   \n"
		"\tiso885914,   \n"
		"\tiso885915,   \n"
		"\tiso885916,   \n"
		"\tus-ascii,    \n"
		"\tutf-8,       \n"
		"\tutf-16,      \n"
		"\tutf-32,      \n"
		"\tucs-2,       \n"
		"\tucs-4,       \n"
		"};\n\n"
		};
}

}


