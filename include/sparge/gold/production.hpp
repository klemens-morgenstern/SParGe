/*
 * Format.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_PRODUCTION_H_
#define SPARGE_GOLD_PRODUCTION_H_

#include <sparge/gold/types.hpp>

namespace sparge
{
namespace gold
{

struct production
{
	static constexpr byte id = 'R';

	integer head_index;

	range<integer> symbols;

	static indexed<production> from_record(const record &r);

};

std::ostream & operator<<(std::ostream & ostr, const production &p);


}
}


#endif /* SPARGE_GOLD_PRODUCTION_H_ */
