/*
 * LALRSte.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_LALRSTATE_H_
#define SPARGE_GOLD_LALRSTATE_H_

#include <sparge/gold/types.hpp>

namespace sparge
{
namespace gold
{

struct record;

struct lalr_state
{
	static constexpr char id = 'L';

	enum action_type_t : integer
	{
		Shift	= 1, ///<This action indicates the symbol is to be shifted. The Target field will contain the index of the state in the LALR State table that the parsing engine will advance to.
		Reduce	= 2, ///<This action denotes that the parser can reduce a rule. The Target field will contain the index of the rule in the Rule Table.
		Goto	= 3, ///<This action is used when a rule is reduced and the parser jumps to the state that represents the shifted nonterminal. The Target field will contain the index of the state in the LALR State table that the parsing engine will jump to after a reduction if completed.
		Accept	= 4, ///<When the parser encounters the Accept action for a given symbol, the source text is accepted as correct and complete. In this case, the Target field is not needed and should be ignored.
	};

	struct action_t
	{
		integer symbol_index;
		action_type_t action;
		integer target_index;
	};


	range<action_t> actions;

	static indexed<lalr_state> from_record(const record &r);

};



}}
#endif /* SPARGE_GOLD_LALRSTATE_H_ */
