/**
 * @file   parser.cpp
 * @date   17.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#include <sparge/core/parser.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/format.hpp>

namespace sparge
{

void parser::plot_dfa(std::ostream& ostr) const
{
	auto f = boost::format("D%1%->D%2%[label=\"%3%\"];\n");


	ostr << "digraph dfa {\n"
			"rankdir=LR;\n"
			"node [shape = doublecircle];\n"
			"D" << dfa << "\n"
			"node [shape = point ];\n"
			"node [shape = circle];\n\n";


	for (auto & p : dfa_states)
	{
		if (!p.second.accept_state)
			ostr << "D" << p.first << ";\n";
		else
			ostr << "D" << p.first << "[color=blue];\n";


		for (const dfa_state::edge & e : p.second.edges)
		{
			auto &c = char_sets.at(e.char_set_idx);
			std::string label;
			label += "[" + boost::locale::conv::from_utf(
					&*c.char_set.begin(),
					&*c.char_set.end(), "utf-8");

		/*	for (auto & x : c.char_ranges)
			{
				label += boost::locale::conv::from_utf(&x.first,  &x.first+1, "utf-8")
						+ "-" +
						boost::locale::conv::from_utf(&x.second, &x.second+1, "utf-8");
			}*/

			label += "]";

			for (auto itr = label.begin(); itr != label.end(); itr++)
			{
				if (*itr == '\n')
				{
					auto pos = itr - label.begin();
					label.replace(itr, itr+1, u8"\\n");
					itr = label.begin() + pos +1 ;
				}
				else if (*itr == '\r')
				{
					auto pos = itr - label.begin();
					label.replace(itr, itr+1, u8"\\r");
					itr = label.begin() + pos +1 ;
				}

			}

			ostr << (f % p.first % e.target % label);

		}

	}
	ostr << "}\n";

}




}


