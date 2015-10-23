
#ifndef SPARGE_CORE_DFA_STATE_H_
#define SPARGE_CORE_DFA_STATE_H_

#include <ostream>
#include <vector>

namespace sparge
{

struct dfa_state
{
	struct edge
	{
		int char_set_idx;
		int target;
	};

	bool accept_state;
	int accept_index;
	std::vector<edge> edges;



};

}



#endif /* EGT_DFASTATE_H_ */
