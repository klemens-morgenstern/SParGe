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
	std::string include_guard;
    std::string ns_in;
    std::string ns_out;
    boost::filesystem::path path;
public:

	parser data;

	void write_symbols()    const;
	void write_dfa_states() const;
	void write_char_set()   const;


	void set_name_space(const std::string &name_space);
	void set_path(const boost::filesystem::path & path);


};

}



#endif /* CORE_GENERATOR_HPP_ */
