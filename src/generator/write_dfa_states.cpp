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

const static std::string token_decl =
		"\n"
		"template<typename Iterator, encoding enc>\n"
		"class token\n"
		"{\n"
		"\tsymbol _symbol;\n"
		"\tsymbol_type _symbol_type;\n"
		"\tIterator _begin;\n"
		"\tIterator _end;\n"
		"public:\n"
		"\tconstexpr token() : _symbol(), _symbol_type(symbol_type::undefined) {}"
		"\tconstexpr token(symbol _symbol, symbol_type _symbol_type, Iterator _begin, Iterator _end)\n"
		"\t\t: _symbol(_symbol), _symbol_type(_symbol_type), _begin(_begin), _end(_end) {};\n"
		"\n"
		"\tusing iterator = Iterator;\n"
		"\tsymbol 		symbol() 	  const {return _symbol; }\n"
		"\tsymbol_type symbol_type() const {return _symbol_type; }\n"
		"\tIterator begin() const {return _begin;}\n"
		"\tIterator end()   const {return _end;}\n"
		"};\n\n"
;


std::string make_cases(int index, std::size_t size)
{
	boost::format f("\tcase char_set<%1%, Encoding>.at(%2%):\n");

	std::stringstream ss;

	for (auto i = 0u; i<size; i++)
		ss << f % index % i ;

	return ss.str();
}

std::string make_edges(const std::map<int, char_set> cs , const dfa_state& st)
{
	std::stringstream ss;

	for (auto &e : st.edges)
	{
		ss << make_cases(e.char_set_idx, cs.at(e.char_set_idx).char_set.size());
		ss << "\t\titr++;\n";
		ss << boost::format("\t\treturn D%1%(itr, end);\n") % e.target;
	}

	return ss.str();
}

std::string make_state(const parser &ps , int idx, const dfa_state& st)
{

	//param 1 is the state index, 2 the eof handling, 3 the edges, 4 the default case.
	boost::format f(
			"template<encoding Encoding, typename Iterator>\n"
			"constexpr token<Encoding,Iterator> D%1%(Iterator &itr, const Iterator& end)\n"
			"{\n"
			"\tif (itr == end)\n"
			"\t\t%2%\n"
			"\tswitch(*itr)\n"
			"\t{\n"
			"%3%\n"
			"\tdefault:\n"
			"\t\t%4%\n"
			"\t}\n"
			"}\n");

	auto a1 = idx;

	auto a3 = make_edges(ps.char_sets, st);

	std::string a2; //eof handling
	std::string a4; //default handling

	if (st.accept_state)
	{
		boost::format f2("return token<Encoding, Iterator>(symbol::%1%, symbol_type::%2%, itr, end);");

		const symbol &s = ps.symbols.at(st.accept_index);
		auto formatted = f2 % boost::locale::conv::from_utf(s.name, "utf-8") % s.type_str();
		a2 = formatted.str();
		a4 = a2;
	}
	else
	{
		a2 = "return token<Encoding, Iterator>(symbol::end_of_file, symbol_type::error, itr, end);";
		a4 = "return token<Encoding, Iterator>(symbol_not_found, symbol_type::error, itr, end);";
	}

	return (f % a1 % a2 % a3 % a4).str();
}

void generator::write_dfa_states() const
{

	auto out = path / "dfa_states.hpp";

    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "TOKENIZER_H_");

    ofs << "#include <" << path.string() << "/symbols.hpp" << ">\n";
    ofs << "#include <" << path.string() << "/char_sets.hpp" << ">\n\n";

    ofs << ns_in;

    /******************************************//* Token type *//******************************************/

    ofs << token_decl;



    for (auto &e : data.dfa_states )
    	ofs << make_state(data, e.first, e.second);

    //starting state
    boost::format f_start("template<encoding Encoding, typename Iterator>\n"
			"constexpr token<Encoding,Iterator> DStart(Iterator &itr, const Iterator& end)\n"
			"{\n"
			"\treturn D%1%(itr, end);\n"
			"}\n");
    ofs << f_start % data.dfa ;

    ofs << ns_out;
    ofs << "\n\n#endif\n";
}
}
