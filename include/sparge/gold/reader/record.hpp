/*
 * record.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_READER_RECORD_H_
#define SPARGE_GOLD_READER_RECORD_H_

#include <sparge/gold/reader/entry.hpp>
#include <vector>
#include <sparge/gold/reader/get_vis.hpp>

namespace sparge {
namespace gold {

struct record
{
	std::vector<entry> entries{};

	static boost::optional<record> read_record(std::istream& str);


};

std::ostream &operator<<(std::ostream& str, const record &e);


}}

#endif /* RECORD_H_ */
