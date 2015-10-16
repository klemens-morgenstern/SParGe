
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/group.hpp>

#include <iostream>

using namespace std;

namespace sparge
{
namespace gold
{
/*	Integer 		Index
	String 			Name
	Integer 		ContainerIndex
	Integer 		StartIndex
	Integer 		EndIndex
	AdvanceMode_t 	AdvanceMode;
	EndingMode_t 	EndingMode
	Empty
	Integer 		NestingCount 	//count of the group

	Range<Integer> GroupIndex;*/

indexed<group_record> group_record::from_record(const record &r)
{
	group_record gc;

	auto idx             = r.entries.at(1).get<integer 		>();
	gc.name              = r.entries.at(2).get<string 		>();
	gc.container_index   = r.entries.at(3).get<integer 		>();
	gc.start_index       = r.entries.at(4).get<integer 		>();
	gc.end_index         = r.entries.at(5).get<integer 		>();
	gc.advance_mode      = static_cast<group_record::advance_mode_t>(r.entries.at(6).get<integer>());
	gc.ending_mode       = static_cast<group_record::ending_mode_t> (r.entries.at(7).get<integer>());

	auto cnt     = r.entries.at(9).get<integer>();

	for (auto i = 0; i<cnt; i++)
		gc.group_index.push_back(r.entries.at(10+i).get<integer>());

	return {idx, gc};
}

}
}

