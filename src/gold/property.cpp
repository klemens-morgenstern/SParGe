#include <sparge/gold/property.hpp>
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/reader/get_vis.hpp>

namespace sparge
{
namespace gold
{
property property::from_record(const record &r)
{
	property p;

	p.index = static_cast<index_t>(r.entries.at(1).get<integer>());
	p.name	= r.entries.at(2).get<string>();
	p.value	= r.entries.at(3).get<string>();

	return p;
}

std::wostream& operator<<(std::wostream& s, const property& p)
{
	s << "idx: " << p.index << " " << p.name << ":" << p.value;
	return s;
}


}
}
