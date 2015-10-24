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

//const static std::string sym_type_tpl =
//		"template<symbol>\n"
//		"symbol_type symbol_type_v = symbol_type::undefined;\n\n";

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
    	"};                 \n"
    	"constexpr static symbol symbol_not_found = static_cast<symbol>(-1);\n"
    	"\n\n"
    };

    boost::format sym_type_v
    	{"\tcase symbol::%1%: return symbol_type::%2%;\n"}
    ;

    boost::format f( "\t%1% = %2%,\n");

    type_vars <<
    		"constexpr symbol_type get_type(symbol sym)\n"
    		"{\n"
    		"\tswitch(sym)\n"
    		"\t{\n";

    for (auto & s : data.symbols)
    {
    	auto nm = boost::locale::conv::from_utf(s.second.name, "utf-8");
    	enum_vals << f % nm % s.first;
		type_vars << sym_type_v % nm % s.second.type_str();
    }

    type_vars <<
        	"\tdefault: return symbol_not_found;\n"
    		"\t}\n};\n\n";


    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "PARSER_H_");
    ofs << ns_in;

    ofs << sym_type;
    ofs << header_f % enum_vals.str() ;
    ofs << type_vars.rdbuf() ;

    ofs << ns_out;
    ofs << "\n\n#endif\n";
}


}


