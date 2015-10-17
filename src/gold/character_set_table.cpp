
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/character_set_table.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/format.hpp>
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

std::ostream& operator<<(std::ostream& ostr, const character_set_table& f)
{

	//ostr << "\nInteger Plane: " << f.unicode_plane << "\n\n";
	ostr << " | " ;
	if (f.characters.size() >0 )
		ostr << boost::locale::conv::from_utf(
				reinterpret_cast<const char16_t*const>(&*f.characters.begin()),
				reinterpret_cast<const char16_t*const>(&*f.characters.end()),
				"utf-8");;

	ostr << " | ";

	if (f.char_ranges.size() > 0)
	{
		for (auto & cs : f.char_ranges)
		{
			auto beg = 	static_cast<char16_t>(cs.begin);
			auto end = 	static_cast<char16_t>(cs.end);


			ostr << boost::format("{ %1%, %2% }, ")
					% boost::locale::conv::from_utf(&beg, &beg+1, "utf-8")
					% boost::locale::conv::from_utf(&end, &end+1, "utf-8");
		}


	}
	ostr << "|\n";
	return ostr;
}



}
}
