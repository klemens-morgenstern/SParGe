
#ifndef SPARGE_CORE_LALR_STATE_HPP_
#define SPARGE_CORE_LALR_STATE_HPP_

#include <vector>

namespace sparge
{

struct symbol;

struct lalr_state
{
	static constexpr char Id = 'L';

	enum action_type
	{
		shift	= 1, ///<This action indicates the symbol is to be shifted. The Target field will contain the index of the state in the LALR State table that the parsing engine will advance to.
		reduce	= 2, ///<This action denotes that the parser can reduce a rule. The Target field will contain the index of the rule in the Rule Table.
		goto_	= 3, ///<This action is used when a rule is reduced and the parser jumps to the state that represents the shifted nonterminal. The Target field will contain the index of the state in the LALR State table that the parsing engine will jump to after a reduction if completed.
		accept	= 4, ///<When the parser encounters the Accept action for a given symbol, the source text is accepted as correct and complete. In this case, the Target field is not needed and should be ignored.
	};

	struct action
	{
		symbol* symbol_index;
		action_type action;
		lalr_state * target;
	};


	std::vector<action> Actions;


};

}



#endif /* DATA_LALR_STATE_HPP_ */
