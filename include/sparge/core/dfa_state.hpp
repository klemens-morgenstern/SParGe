
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
		bool inverted;
	};

	bool accept_state;
	int accept_index;
	std::vector<edge> edges;


	std::string write_doxy(std::ostream& ostr) const;

};

}



#endif /* EGT_DFASTATE_H_ */
