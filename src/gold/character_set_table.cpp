
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/character_set_table.hpp>

#include <iostream>

using namespace std;

namespace sparge
{
namespace gold
{

indexed<character_set_table> character_set_table::from_record(const record &r)
{
	character_set_table cs;

	auto Idx		 = r.entries.at(1).get<integer>();
	cs.unicode_plane = r.entries.at(2).get<integer>();

	auto cnt = r.entries.at(3).get<integer>();

	for (auto i = 0; i< cnt*2; i+=2)
	{
		///the mother returns a range!
		auto beg = r.entries.at(5+i).get<integer>();
		auto end = r.entries.at(6+i).get<integer>();

		if (beg == end)
			cs.characters.push_back(beg);
		else
			cs.char_ranges.push_back(char_range(beg, end));
	}
	return {Idx, cs};
}

}
}
