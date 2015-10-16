/*
 * file.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_READER_FILE_H_
#define SPARGE_GOLD_READER_FILE_H_

#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/types.hpp>
#include <istream>
#include <vector>

namespace sparge {
namespace gold {

struct raw_file
{
	string name;
	range<record> records;


	static raw_file load_file(const std::string &filename);

};


std::istream &operator>>(std::istream& str,  raw_file &e);




}}
#endif /* FILE_H_ */
