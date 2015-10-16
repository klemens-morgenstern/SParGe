/*
 * structure.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_CHARACTER_SET_TABLE_H_
#define SPARGE_GOLD_CHARACTER_SET_TABLE_H_

#include <sparge/gold/types.hpp>
#include <ostream>

namespace sparge
{
namespace gold
{

struct record;
//byte 'c'
struct character_set_table
{
	static constexpr byte id = 'c';

	integer unicode_plane;
	//Integer RangeCount;

	struct char_range
	{
		integer begin;
		integer end;
		char_range(integer beg, integer end) : begin(beg), end(end) {};
		char_range(const char_range&) = default;
		char_range() = default;
	};

	range<integer> characters;
	range<char_range> char_ranges;

	static indexed<character_set_table> from_record(const record &r);

};

std::wostream& operator<<(std::wostream& s, const character_set_table& f);


}
}


#endif /* SPARGE_GOLD_CHARACTERSETTABLE_H_ */
