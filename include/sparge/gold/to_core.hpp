/**
 * @file   to_core.hpp
 * @date   17.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef GOLD_TO_CORE_HPP_
#define GOLD_TO_CORE_HPP_

#include <sparge/core/parser.hpp>
#include <sparge/gold/file.hpp>

namespace sparge
{
namespace gold
{

sparge::parser to_core(const file & f);

}
}



#endif /* GOLD_TO_CORE_HPP_ */
