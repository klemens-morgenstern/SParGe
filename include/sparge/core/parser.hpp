
#ifndef SPARGE_CORE_PARSER_HPP_
#define SPARGE_CORE_PARSER_HPP_

#include <sparge/core/dfa_state.hpp>
#include <sparge/core/lalr_state.hpp>
#include <sparge/core/symbol.hpp>
#include <sparge/core/dfa_group.hpp>
#include <vector>

namespace sparge
{
struct parser
{
	std::vector<dfa_state>  dfa_states;
	std::vector<lalr_state> lalr_states;
	std::vector<dfa_group>  dfa_groups;
	std::vector<symbol>		symbols;

	dfa_state* dfa;
	lalr_state* lalr;

};


}

#endif /* DATA_PARSER_HPP_ */
