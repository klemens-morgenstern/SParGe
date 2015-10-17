
#include <sparge/gold/table_counts.hpp>
#include <sparge/gold/reader/record.hpp>
#include <boost/format.hpp>

using namespace std;

namespace sparge
{

namespace gold
{

table_counts table_counts::from_record(const record &r)
{
	table_counts tc;

	tc.symbol_table = r.entries.at(1).get<integer>();
	tc.set_table    = r.entries.at(2).get<integer>();
	tc.rule_table   = r.entries.at(3).get<integer>();
	tc.dfa_table    = r.entries.at(4).get<integer>();
	tc.lalr_table   = r.entries.at(5).get<integer>();
	tc.group_table  = r.entries.at(6).get<integer>();

	return tc;
}

ostream &operator<<(ostream& ostr, const table_counts &e)
{

	ostr << "| Table Name  | Count |\n"
			"|-------------|-------|\n";

	auto fr = boost::format("| %1% | %2% |\n");

	ostr << fr % "Symbols" % e.symbol_table;


	ostr << fr % "Symbols"     		 % e.symbol_table;
	ostr << fr % "Character Sets "   % e.set_table   ;
	ostr << fr % "Rules "  			 % e.rule_table  ;
	ostr << fr % "Dfa States "   	 % e.dfa_table   ;
	ostr << fr % "Lalr States "  	 % e.lalr_table  ;
	ostr << fr % "Groups " 			 % e.group_table ;

	ostr << "\n";
	return ostr;
}

}
}
