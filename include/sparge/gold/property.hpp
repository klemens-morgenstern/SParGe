/*
 * property.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_PROPERTY_H_
#define SPARGE_GOLD_PROPERTY_H_

#include <sparge/gold/types.hpp>
#include <ostream>

namespace sparge {
namespace gold {

struct record;

/** Property record
 * | Byte 	  | Integer | String | String |
 * |----------|---------|--------|--------|
 * | 'P'/112  | Index   | Name   | Value  |
 */

struct property
{
	static constexpr byte id = 'p';


	enum index_t : integer
	{
		NameIdx				= 0,
		Version				= 1,
		Author				= 2,
		About				= 3,
		Character_Set		= 4,
		Character_Mapping	= 5,
		Generated_Date		= 6,
		Generated_By		= 7,
	};

	index_t index;
	string name;
	string value;

	static property from_record(const record &r);

};

std::ostream& operator<<(std::ostream& s, const property& f);

}
}
#endif /* SPARGE_GOLD_PROPERTY_H_ */
