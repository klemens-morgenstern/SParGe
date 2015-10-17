
#include <sparge/gold/dfa_state.hpp>
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/reader/get_vis.hpp>

namespace sparge
{
namespace gold
{


indexed<dfa_state> dfa_state::from_record(const record &r)
{
	dfa_state p;

	auto idx 		= r.entries.at(1).get<integer>();
	p.accept_state	= r.entries.at(2).get<boolean>();
	p.accept_index	= r.entries.at(3).get<integer>();

	for (auto i = 5u; i<r.entries.size(); i+=3)
	{
		edge edg;
		edg.char_set_index = r.entries.at(i).  get<integer>();
		edg.target_index   = r.entries.at(i+1).get<integer>();
		p.edges.push_back(edg);

	}

	return {idx, p};
}

std::ostream & operator<<(std::ostream & ostr, const dfa_state &f)
{
	ostr << " - Accept: " << f.accept_state ? "true \n" : "false\n";
	ostr << " - Accept Index: " << f.accept_index << "\n";



	ostr << "| Char Set Index | Target Index |\n"
			"|----------------|--------------|\n";

	for (auto & e : f.edges)
		ostr << "| " << e.char_set_index  << " | " << e.target_index << "|\n";

	ostr << "\n";
	return ostr;
}

}
}
