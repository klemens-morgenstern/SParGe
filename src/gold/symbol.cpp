
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/symbol.hpp>


using namespace std;

namespace sparge
{
namespace gold
{

indexed<symbol> symbol::from_record(const record &r)
{
	symbol cs;

	auto idx 	= r.entries.at(1).get<integer>();
	cs.name 	= r.entries.at(2).get<string>();
	cs.type 	= static_cast<symbol::type_t>(r.entries.at(3).get<integer>());

	return {idx, cs};
}


}
}

