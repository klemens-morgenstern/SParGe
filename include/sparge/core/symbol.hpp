
#ifndef SPARGE_CORE_SYMBOL_HPP_
#define SPARGE_CORE_SYMBOL_HPP_

#include <string>

namespace sparge
{
struct symbol
{

	enum type_t
	{
		nonterminal = 0,
		terminal 	= 1,
		noise 		= 2,
		end_of_file	= 3,
		group_start	= 4,
		group_end 	= 5,
		decrement 	= 6, //deprecated
		error		= 7,
	};

	std::u32string name;
	type_t type;
};

}



#endif /* DATA_SYMBOL_HPP_ */
