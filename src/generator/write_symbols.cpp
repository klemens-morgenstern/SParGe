/**
 * @file   write_symbols.cpp
 * @date   18.10.2015
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

const static std::string sym_type =
		"enum class symbol_type\n"
		"{\n"
		"\tundefined,\n"
		"\tend_of_file,\n"
		"\terror,\n"
		"\tnoise,\n"
		"\tgroup_start,\n"
		"\tgroup_end,\n"
		"\tterminal,\n"
		"\tnonterminal,\n"
		"};\n\n";

const static std::string sym_type_tpl =
		"template<symbol>\n"
		"symbol_type symbol_type_v = symbol_type::undefined;\n\n";

void generator::write_symbols() const
{

	auto out = path / "symbols.hpp";

// this is beyond the header data

    std::stringstream type_vars;
    std::stringstream enum_vals;

    boost::format header_f {
    	"enum class symbol  \n"
    	"{                  \n"
    	"%1%                \n"
    	"};                 \n\n\n"
    };

    boost::format sym_type_v
    	{"template<> symbol_type symbol_type_v<symbol::%1%> = symbol_type::%2%;\n"}
    ;

    boost::format f( "\t%1% = %2%,\n");

    for (auto & s : data.symbols)
    {
    	auto nm = boost::locale::conv::from_utf(s.second.name, "utf-8");
    	enum_vals << f % nm % s.first;

    	switch (s.second.type)
    	{
    	case symbol::end_of_file: type_vars << sym_type_v % nm % "end_of_file"; break;
    	case symbol::error:       type_vars << sym_type_v % nm % "error"      ; break;
    	case symbol::noise:       type_vars << sym_type_v % nm % "noise"      ; break;
    	case symbol::group_start: type_vars << sym_type_v % nm % "group_start"; break;
    	case symbol::group_end:   type_vars << sym_type_v % nm % "group_end"  ; break;
    	case symbol::terminal:    type_vars << sym_type_v % nm % "terminal"   ; break;
    	case symbol::nonterminal: type_vars << sym_type_v % nm % "nonterminal"; break;
    	}
    }


    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "PARSER_H_");
    ofs << ns_in;


    ofs << sym_type;
    ofs << sym_type_tpl;
    ofs << header_f % enum_vals.str() ;
    ofs << type_vars.rdbuf() ;

    ofs << ns_out;
    ofs << "\n\n#endif\n";
}


}


