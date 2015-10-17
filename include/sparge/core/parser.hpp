
#ifndef SPARGE_CORE_PARSER_HPP_
#define SPARGE_CORE_PARSER_HPP_

#include <sparge/core/dfa_state.hpp>
#include <sparge/core/lalr_state.hpp>
#include <sparge/core/symbol.hpp>
#include <sparge/core/token_group.hpp>
#include <map>

namespace sparge
{
struct parser
{
	std::u32string generator	 	;
	std::u32string generator_version;
	std::u32string name				;
	std::u32string version			;
	std::u32string author			;
	std::u32string about			;
	std::u32string generated_by		;
	std::u32string generated_date 	;

	std::map<int, dfa_state>   dfa_states;
	std::map<int, lalr_state>  lalr_states;
	std::map<int, symbol>	   symbols;
	std::map<int, token_group> token_groups;

	int dfa;
	int lalr;


	void plot_dfa(std::ostream& ostr) const;

};


}

#endif /* DATA_PARSER_HPP_ */
