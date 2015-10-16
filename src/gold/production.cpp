
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/production.hpp>

using namespace std;

namespace sparge
{
namespace gold
{

indexed<production> production::from_record(const record &r)
{
	production cs;

	auto idx		= r.entries.at(1).get<integer>();
	cs.head_index 	= r.entries.at(2).get<integer>();

	for (auto itr = r.entries.begin() + 4; itr != r.entries.end(); itr++)
		cs.symbols.push_back(itr->get<integer>());

	return {idx, cs};
}

}
}



