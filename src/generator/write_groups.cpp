/**
 * @file   write_groups.cpp
 * @date   24.10.2015
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

namespace sparge
{
void generator::write_groups() const
{
	auto out = path / "groups.hpp";

    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "GROUPS_H_");

    ofs << "#include <" << path.string() << "/dfa_states.hpp" << ">\n";

    ofs << ns_in;

    /******************************************//* The basic group executor *//******************************************/

    //basic group executor,
    boost::format f(
    "template<typename Iterator, encoding Encoding>\n"
    "finding<Iterator, Encoding> G%1%(Iterator & itr, const Iterator &end)\n"
    "{\n"
    "\twhile (itr != end)\n"
    "\t{\n"
    "\t\tauto tk = DStart(itr, end);\n"
    "\t\tif (tk.symbol() == symbol::%2%)\n"
    "\t\t{"
    "\t\t%3%\n"
    "\t\t\treturn finding<Iterator, Encoding>(symbol::%4%, symbol_type::%5%, itr);\n"
    "\t\t}\n"
    "\t\t%6%\n"
    "\t}\n"
    "\treturn finding<Iterator, Encoding>(symbol::end_of_file, symbol_type::error, itr);\n"
    "};\n\n");


    for (auto & g : data.token_groups)
    {
    	const symbol &end = data.symbols.at(g.second.end);
    	const symbol &sym = data.symbols.at(g.second.container);

    	std::string consume =
    			g.second.advange_mode == token_group::token ?
    				"itr = tk.pos();"
    			:	"itr++;"
    			;

    	std::string ending;
    	if (g.second.ending_mode == token_group::closed)
    		ending = consume;

    	ofs <<  f
				% g.first //index
				% boost::locale::conv::from_utf(end.name, "utf8") //symbol
    			% ending //ending mode, i.e. consume the last one or not.
				% boost::locale::conv::from_utf(sym.name, "utf8")//symbol name
				% sym.type_str()//symbol type
				% consume//advancde mode
				;
    }

    ofs << ns_out;
    ofs << "\n\n#endif\n";
}

}


