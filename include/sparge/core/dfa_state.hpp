
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
		std::vector<char32_t> char_set;
		std::vector<std::pair<char32_t, char32_t>> char_ranges;
		int  target;
		bool inverted = false; //that means, that every char except for the ones in the list can be used.
	};

	bool accept_state;
	int accept_index;
	std::vector<edge> edges;



};

}



#endif /* EGT_DFASTATE_H_ */
