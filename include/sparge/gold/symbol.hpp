
#ifndef SPARGE_GOLD_SYMBOL_H_
#define SPARGE_GOLD_SYMBOL_H_

#include <sparge/gold/types.hpp>
#include <iostream>

namespace sparge
{
namespace gold
{
struct record;


struct symbol
{
	static constexpr byte id = 'S';

	enum type_t : integer
	{
		Nonterminal = 0,
		Terminal 	= 1,
		Noise 		= 2,
		EndOfFile 	= 3,
		GroupStart 	= 4,
		GroupEnd 	= 5,
		Decrement 	= 6, //deprecated
		Error		= 7,
	};

	string name;
	type_t type;

	static indexed<symbol> from_record(const record &r);

};

}

}

#endif /* SPARGE_GOLD_SYMBOL_H_ */
