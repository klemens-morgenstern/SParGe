
#ifndef SPARGE_CORE_PARSER_HPP_
#define SPARGE_CORE_PARSER_HPP_

#include <dfa_state.hpp>
#include <lalr_state.hpp>

namespace sparge
{
struct parser
{
	dfa_state* dfa;
	lalr_state* lalr;
};


}



#endif /* DATA_PARSER_HPP_ */
