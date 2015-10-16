
#include <type_traits>
#include <sparge/gold/file.hpp>
#include <sparge/gold/reader/get_vis.hpp>
#include <cassert>

using namespace std;
namespace sparge
{
namespace gold
{

void file::add_property(const property &prop)
{
	switch (prop.index)
	{
	case property::NameIdx:				name 			 = prop.value; break;
	case property::Version:				version			 = prop.value; break;
	case property::Author:				author			 = prop.value; break;
	case property::About:				about			 = prop.value; break;
	case property::Character_Set:		character_set 	 = prop.value; break;
	case property::Character_Mapping:	character_mapping= prop.value; break;
	case property::Generated_Date:		generated_date 	 = prop.value; break;
	case property::Generated_By:		generated_by 	 = prop.value; break;
	}
}


void file::add_record(const record &r )
{
	switch(r.entries.at(0).get<byte>())
	{
	case property::id:
		add_property(property::from_record(r));
		break;
	case table_counts::id:
		this->table_counts = table_counts::from_record(r);
		break;
	case character_set_table::id:
		this->character_set_tables.emplace(character_set_table::from_record(r));
		break;
	case symbol::id:
		this->symbol_table.emplace(symbol::from_record(r));
		break;
	case group_record::id:
		group_records.emplace(group_record::from_record(r));
		break;
	case production::id:
		productions.emplace(production::from_record(r));
		break;
	case initial_states::id:
		initial_states = initial_states::from_record(r);
		break;
	case dfa_state::id:

		dfa_states.emplace(dfa_state::from_record(r));
		break;
	case lalr_state::id:
		lalr_states.emplace(lalr_state::from_record(r));
		break;
	}
}


file read_raw_file(const std::string & rf) {return read_raw_file(raw_file::load_file(rf));}
file read_raw_file(const raw_file & rf)
{
	using namespace std;

	file f;

	f.gold_version = rf.name;

	for (auto &rec : rf.records)
		f.add_record(rec);

	assert(f.symbol_table.size()			== f.table_counts.symbol_table );
	assert(f.character_set_tables.size()	== f.table_counts.set_table    );
	assert(f.productions.size()				== f.table_counts.rule_table   );
	assert(f.dfa_states.size()				== f.table_counts.dfa_table    );
	assert(f.lalr_states.size()				== f.table_counts.lalr_table   );
	assert(f.group_records.size()			== f.table_counts.group_table  );

	for (auto &g : f.group_records)
	{
		cout << "Group: "
			 << static_cast<int>(g.second.advance_mode) << endl;
		cout << g.second.container_index << endl;
		cout << static_cast<int>(g.second.end_index) << endl;
		cout << g.second.ending_mode << endl;

		wcout << g.second.name << endl;

		for (auto &s : g.second.group_index)
			cout << s << ", ";

		cout << endl << endl;
	}

	return f;
}



}
}
