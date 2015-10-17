
#ifndef SPARGE_GOLD_TYPES_H_
#define SPARGE_GOLD_TYPES_H_

#include <cstdint>
#include <vector>
#include <string>
#include <boost/blank.hpp>
#include <istream>
#include <map>


namespace sparge
{
namespace gold
{
using integer 	= std::uint16_t;
template<typename T>
using range		= std::vector<T>;
using string  	= std::u16string;
using byte		= char;
using boolean	= bool;
using blank 	= boost::blank;


//template<typename T> using Map  	= std::map <Integer, T>;

template<typename T> struct map : std::map<integer, T> {};
template<typename T> using indexed 	= std::pair<integer, T>;


inline string read_string(std::istream &ss)
{
	string name;

	while (!ss.eof())
	{
		wchar_t value = 0xFFFF;
		ss.read(reinterpret_cast<char*>(&value), 2);
		if (value == '\0')
			break;

		name.push_back(value);
	}

	return name;
}

}
}


#endif /* SPARGE_GOLD_TYPES_H_ */
