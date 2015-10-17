/**
 * @file   to_core.cpp
 * @date   17.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#include <boost/locale/utf.hpp>
#include <sparge/gold/to_core.hpp>
#include <boost/locale/encoding.hpp>
#include <algorithm>
#include <iterator>


namespace sparge
{
namespace gold
{

sparge::parser to_core(const file & f)
{
	sparge::parser p;
	using boost::locale::conv::utf_to_utf;

	p.generator_version	 = utf_to_utf<char32_t, char16_t>(f.gold_version);
	p.generator		 = U"Gold Parser System";

	p.author 		 = utf_to_utf<char32_t, char16_t>(f.author		    );
	p.name			 = utf_to_utf<char32_t, char16_t>(f.name			);
	p.version		 = utf_to_utf<char32_t, char16_t>(f.version			);
	p.author		 = utf_to_utf<char32_t, char16_t>(f.author			);
	p.about			 = utf_to_utf<char32_t, char16_t>(f.about			);
	p.generated_by	 = utf_to_utf<char32_t, char16_t>(f.generated_by	);
	p.generated_date = utf_to_utf<char32_t, char16_t>(f.generated_date 	);

	auto dfa_edge_c = [&](const dfa_state::edge & e)
		{
			character_set_table cs = f.character_set_tables.at(e.char_set_index);

			auto st = utf_to_utf<char32_t, char16_t>(
					reinterpret_cast<const char16_t *>(&*cs.characters.begin()),
					reinterpret_cast<const char16_t *>(&*cs.characters.end()));

			sparge::dfa_state::edge ret;
			ret.target = e.target_index;

			auto ch_t = [](const character_set_table::char_range & c)
				{
					std::pair<char32_t, char32_t> ret =
					{
							utf_to_utf<char32_t, char16_t>(
									reinterpret_cast<const char16_t *>(&c.begin),
									reinterpret_cast<const char16_t *>(&c.begin+1))[0],
							utf_to_utf<char32_t, char16_t>(
									reinterpret_cast<const char16_t *>(&c.end),
									reinterpret_cast<const char16_t *>(&c.end+1))[0]
					};
					return ret;
				};

			ret.char_ranges.resize(cs.char_ranges.size());
			std::transform(	 cs.char_ranges.begin(),  cs.char_ranges.end(),
							ret.char_ranges.begin(), //ret.char_ranges.end(),
							ch_t);

			ret.char_set.assign(st.begin(), st.end());
			ret.inverted = false;
			return ret;
		};


	auto dfa_conv = [&](const dfa_state & in)
		{
			sparge::dfa_state out;

			out.accept_index = in.accept_index;
			out.accept_state = in.accept_state;

			out.edges.resize(in.edges.size());

			std::transform(in.edges.begin(), in.edges.end(),
						out.edges.begin(), dfa_edge_c);

			return out;
		};

	int dfa_cnt = 0;

	std::transform(f.dfa_states.begin(), f.dfa_states.end(),
				std::inserter(p.dfa_states, p.dfa_states.end()),
				[&](const std::pair<std::uint16_t, dfa_state> &p)
				{

					if (p.first >= dfa_cnt)
						dfa_cnt = p.first +1;
					return std::pair<int, sparge::dfa_state>
					{
						p.first,
						dfa_conv(p.second)
					};
				});



	return p;

}

}
}
