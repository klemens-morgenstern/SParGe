/*
 * DFAState.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_DFASTATE_H_
#define SPARGE_GOLD_DFASTATE_H_

#include <sparge/gold/types.hpp>
#include <ostream>

namespace sparge
{
namespace gold
{
struct record;

struct dfa_state
{
	static constexpr byte id = 'D';

	struct edge
	{
		integer char_set_index;
		integer target_index;
	};

	boolean accept_state;
	integer accept_index;

	range<edge> edges;

	static indexed<dfa_state> from_record(const record &r);


};

std::ostream & operator<<(std::ostream & ostr, const dfa_state &f);

}
}

#endif /* SPARGE_GOLD_DFASTATE_H_ */
