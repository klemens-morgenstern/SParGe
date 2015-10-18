/**
 * @file   production.hpp
 * @date   18.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef CORE_PRODUCTION_HPP_
#define CORE_PRODUCTION_HPP_

namespace sparge
{

struct production
{
	int head_index;

	std::vector<int> symbols;
};

}

#endif /* CORE_PRODUCTION_HPP_ */
