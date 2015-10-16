
#ifndef SPARGE_CORE_DFA_STATE_H_
#define SPARGE_CORE_DFA_STATE_H_

#include <ostream>

namespace sparge
{

struct dfa_state
{
	struct edge
	{
		std::vector<char32_t> char_set;
		dfa_state*  target;
	};

	bool accept_state;
	dfa_state* accept_index;
	std::vector<edge> edges;



};

}



#endif /* EGT_DFASTATE_H_ */
