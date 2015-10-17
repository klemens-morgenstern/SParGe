/*
 * Group.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_GROUP_H_
#define SPARGE_GOLD_GROUP_H_

#include <sparge/gold/types.hpp>

namespace sparge
{
namespace gold
{


struct group_record
{
	static constexpr char id = 'g';

	enum advance_mode_t : integer
	{
		Token 	  = 0, ///<	The group will advance a token at a time.
		Character = 1, ///<	The group will advance by just one character at a time.
	};


	enum ending_mode_t : integer
	{
		Open 	= 0, ///<	The ending symbol will be left on the input queue.
		Closed 	= 1, ///<	The ending symbol will be consumed.
	};

	string name;
	integer container_index;
	integer start_index;
	integer end_index;
	advance_mode_t advance_mode;
	ending_mode_t ending_mode;

	range<integer> group_index;

	static indexed<group_record> from_record(const record &r);
};


std::ostream & operator<<(std::ostream & ostr, const group_record &f);


}
}


#endif /* SPARGE_GOLD_GROUP_H_ */
