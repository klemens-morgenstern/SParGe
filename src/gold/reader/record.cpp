
#include <sparge/gold/reader/record.hpp>

#include <iostream>
using namespace std;

namespace sparge
{
namespace gold
{

boost::optional<record> record::read_record(std::istream& str)
{
	if (str.peek() == 'M')
	{
		char M;
		str >> M; //read the 'M'
		uint16_t cnt;

		str.read(reinterpret_cast<char*>(&cnt), 2);

		record r;

		for (uint16_t i = 0; i<cnt; i++)
		{
			r.entries.push_back(entry::read_entry(str));
		}

		return r;
	}
	else return boost::none;
}

std::wostream &operator<<(std::wostream& str, const record &e)
{
	str << "Record" << endl;
	for (auto &x : e.entries)
	{
		str << "   " << e << endl;
	}

	str << endl;

	return str;
}}


} /* namespace Gpp */
