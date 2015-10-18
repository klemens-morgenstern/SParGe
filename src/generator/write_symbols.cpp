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

#include <string>
#include <vector>


namespace sparge
{

const static boost::format header_f =
	"enum class EndOfFile  "
	"{                     "
	"	%1%                "
	"};                    "
	"enum class Error	   "
	"{                     "
	"	%2%                "
	"};                    "
	"                      "
	"enum class Noise      "
	"{                     "
	"	%3%                "
	"};                    "
    "                      "
	"enum class GroupStart "
	"{                     "
	"	%4%                "
	"};                    "
	"enum class GroupEnd   "
	"{                     "
	"	%5%                "
	"};                    "
	"enum class Terminal   "
	"{                     "
	"	%6%                "
	"};                    "
	"enum class Nonterminal"
	"{                     "
	"	%7%                "
	"};                    "
;



void generator::write_symbols(const boost::filesystem::path & p)
{
	boost::filesystem::create_directories(p);

	auto out = p / "symbols.hpp";

	std::vector< std::string > ns;

    boost::iter_split(ns, name_space, boost::algorithm::first_finder("::"));

    auto ns_f = boost::format("namespace %1%\n{");

    std::string include_guard;
    std::string ns_in;
    for (auto &n : ns)
    {
    	include_guard += n + "_";
    	ns_in += (ns_f % n).str();
    }
    boost::to_upper(include_guard);

    std::string ns_out("}\n", ns.size());

// this is beyond the header data

    std::string sEndOfFile   ;
    std::string sError	    ;
    std::string sNoise       ;
    std::string sGroupStart  ;
    std::string sGroupEnd    ;
    std::string sTerminal    ;
    std::string sNonterminal ;

    boost::format f = "\t%1% = %2%,\n";

    for (auto & s : data.symbols)
    {
    	switch (s.second.type)
    	{
    	case symbol::end_of_file: sEndOfFile   += "";
    	case symbol::error:       sError       += "";
    	case symbol::noise:       sNoise       += "";
    	case symbol::group_start: sGroupStart  += "";
    	case symbol::group_end:   sGroupEnd    += "";
    	case symbol::terminal:    sTerminal    += "";
    	case symbol::nonterminal: sNonterminal += "";
    	}
    }


}


}


