
#include <sparge/gold/table_counts.hpp>
#include <sparge/gold/reader/record.hpp>

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

wostream &operator<<(wostream& str, const table_counts &e)
{
	str << "==================== table counts ====================" << endl;

	str << "\tsymboltable: " << e.symbol_table << endl;
	str << "\tsettable   : " << e.set_table    << endl;
	str << "\truletable  : " << e.rule_table   << endl;
	str << "\tdfatable   : " << e.dfa_table    << endl;
	str << "\tlalrtable  : " << e.lalr_table   << endl;
	str << "\tgrouptable : " << e.group_table  << endl;

	return str;
}

}
}
