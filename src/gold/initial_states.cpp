
#include <sparge/gold/initial_states.hpp>
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/reader/get_vis.hpp>

using namespace std;

namespace sparge
{
namespace gold
{
initial_states initial_states::from_record(const record &r)
{
	initial_states p;

	p.dfa	= r.entries.at(1).get<integer>();
	p.lalr	= r.entries.at(2).get<integer>();

	return p;
}

std::wostream& operator<<(std::wostream& s, const initial_states& p)
{
	s << "==================== Production ====================" << endl;
	s << "\tDFA : " << p.dfa << endl;
	s << "\tLALR: " << p.lalr << endl;
	return s;
}


}
}

