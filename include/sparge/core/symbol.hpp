
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

	std::string type_str() const
	{
		switch (type)
		{
		case nonterminal: return "nonterminal";
		case terminal 	: return "terminal";
		case noise 		: return "noise";
		case end_of_file: return "end_of_file";
		case group_start: return "group_start";
		case group_end 	: return "group_end";
		case decrement 	: return "decrement";
		case error		: return "error";
		default:
			return "";
		}
	}

};

}



#endif /* DATA_SYMBOL_HPP_ */
