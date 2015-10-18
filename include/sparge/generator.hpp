/**
 * @file   generator.hpp
 * @date   18.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef CORE_GENERATOR_HPP_
#define CORE_GENERATOR_HPP_

#include <string>
#include <sparge/core/parser.hpp>
#include <boost/filesystem/path.hpp>
namespace sparge
{

struct generator
{
	parser data;
	std::string name_space;

	void write_symbols(const boost::filesystem::path & p);

};

}



#endif /* CORE_GENERATOR_HPP_ */
