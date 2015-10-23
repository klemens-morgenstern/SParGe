/**
 * @file   char_set.hpp
 * @date   23.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef SPARGE_CORE_CHAR_SET_HPP_
#define SPARGE_CORE_CHAR_SET_HPP_


namespace sparge
{

struct char_set
{
	std::vector<char32_t> char_set;
	std::vector<std::pair<char32_t, char32_t>> char_ranges;
};

}



#endif /* CHAR_SET_HPP_ */
