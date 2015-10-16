/*
 * InitialStates.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_INITIALSTATES_H_
#define SPARGE_GOLD_INITIALSTATES_H_


#include <sparge/gold/types.hpp>
#include <ostream>

namespace sparge
{
namespace gold
{

struct record;

struct initial_states
{
	static constexpr byte id = 'I';

	integer dfa;
	integer lalr;

	static initial_states from_record(const record &r);

};

std::wostream& operator<<(std::wostream& s, const initial_states& f);

}
}
#endif /* SPARGE_GOLD_INITIALSTATES_H_ */
