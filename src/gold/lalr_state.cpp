
#include <sparge/gold/lalr_state.hpp>
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/reader/get_vis.hpp>

namespace sparge
{
namespace gold
{

indexed<lalr_state> lalr_state::from_record(const record &r)
{
	lalr_state p;

	auto idx = r.entries.at(1).get<integer>();

	for (auto i = 3u; i<r.entries.size(); i+=4)
	{
		action_t a;
		a.symbol_index = r.entries.at(i).  get<integer>();
		a.action 	     = static_cast<action_type_t>(r.entries.at(i+1).get<integer>());
		a.target_index = r.entries.at(i+2).get<integer>();

		p.actions.push_back(a);

	}

	return {idx, p};
}


}

}

