/**
 * @file   token_group.hpp
 * @date   17.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef CORE_TOKEN_GROUP_HPP_
#define CORE_TOKEN_GROUP_HPP_

#include <string>

namespace sparge
{

struct dfa_group
{

	enum
	{
		Token 	 , ///<	The group will advance a token at a time.
		Character, ///<	The group will advance by just one character at a time.
	} advange_mode;


	enum
	{
		Open , ///<	The ending symbol will be left on the input queue.
		Close, ///<	The ending symbol will be consumed.
	} ending_mode;

	std::u32string name;
	int container;
	int start;
	int end;

	std::vector<dfa_group*> group_index;

};

}


#endif /* CORE_TOKEN_GROUP_HPP_ */
