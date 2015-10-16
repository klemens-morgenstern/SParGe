/*
 * entry.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_READER_ENTRY_H_
#define SPARGE_GOLD_READER_ENTRY_H_

#include <sparge/gold/types.hpp>
#include <sparge/gold/reader/get_vis.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <ostream>
#include <istream>
#include <cstdint>

namespace sparge {
namespace gold {

class entry
{
public:
	typedef boost::variant<boost::none_t, byte, boolean, integer, string> data_t;
	data_t data = boost::none;
	entry() = default;
	entry(entry && )= default;
	entry(const entry & )= default;
	entry(data_t dat) : data(dat) {};

	template<typename T>
	T get() const
	{
		get_vis<T> vis;
		return data.apply_visitor(vis);
	}
	static entry read_entry(std::istream& str);

};



std::wostream &operator<<(std::wostream& str, const entry &e);

}
}
#endif /* ENTRY_H_ */
