#include <sparge/gold/property.hpp>
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/reader/get_vis.hpp>
#include <locale>
#include <boost/locale/encoding.hpp>

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

std::ostream& operator<<(std::ostream& s, const property& p)
{
	s << "idx: " << p.index << " " <<
			boost::locale::conv::from_utf(p.name, std::locale().name()) << ":" <<
			boost::locale::conv::from_utf(p.value, std::locale().name());
	return s;
}


}
}
