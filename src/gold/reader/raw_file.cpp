
#include <sparge/gold/reader/raw_file.hpp>

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

using namespace std;

namespace sparge
{
namespace gold
{

std::istream &operator>>(std::istream& str,  raw_file &e)
{
	if (!str.eof())
		e.name = read_string(str);


	while (!str.eof())
	{
		auto rec = record::read_record(str);
		if (rec)
			e.records.push_back(*rec);
		else
			return str;
	}
	return str;

}

raw_file raw_file::load_file(const std::string &filename)
{
	ifstream str(filename, std::ios::binary);
	stringstream ss;
	ss << str.rdbuf();

	raw_file rf;
	ss >> rf;

	if (!ss.eof())
		throw std::ios_base::failure("File " + filename + " could not be loaded completyl");

	return rf;
}


}}


