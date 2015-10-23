/**
 * @file   generator.cpp
 * @date   21.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#include <sparge/generator.hpp>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

namespace sparge
{




void generator::set_name_space(const std::string &name_space)
{
	std::vector< std::string > ns;

    boost::iter_split(ns, name_space, boost::algorithm::first_finder("::"));

    ns.push_back("parser");
    auto ns_f = boost::format("namespace %1%\n{\n");
    auto ns_f2 = boost::format("} /* %1% */\n");
    std::string include_guard;
    std::string ns_in;
    std::string ns_out;
    for (auto &n : ns)
    {
    	include_guard += n + "_";
    	ns_in  += (ns_f  % n).str();
    	ns_out = (ns_f2 % n).str() + ns_out;
    }
    boost::to_upper(include_guard);

    this->ns_in = ns_in;
    this->ns_out = ns_out;
    this->include_guard = include_guard;
}



void generator::set_path(const boost::filesystem::path& path)
{
	this->path = path;
	boost::filesystem::create_directories(path);
}

}
