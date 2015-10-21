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
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
namespace sparge
{
namespace gold
{


void transform_dfa (sparge::parser &p, const file &f)
{
	using boost::locale::conv::utf_to_utf;


	auto dfa_edge_step = [&](const character_set_table & cs, std::uint16_t target)
		{
			auto st = utf_to_utf<char32_t, char16_t>(
					reinterpret_cast<const char16_t *>(&*cs.characters.begin()),
					reinterpret_cast<const char16_t *>(&*cs.characters.end()));

			sparge::dfa_state::edge ret;
			ret.target = target;

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
			return ret;
		};

	auto dfa_edge_c = [&](const dfa_state::edge & e)
		{
			return  dfa_edge_step(f.character_set_tables.at(e.char_set_index), e.target_index);
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


	std::transform(f.dfa_states.begin(), f.dfa_states.end(),
				std::inserter(p.dfa_states, p.dfa_states.end()),
				[&](const std::pair<std::uint16_t, dfa_state> &p)
				{

					std::pair<int, sparge::dfa_state> ret
					{
						p.first,
						dfa_conv(p.second)
					};

					return ret;
				});
}

void transform_sym (sparge::parser &p, const file &f)
{
	using boost::locale::conv::utf_to_utf;

	auto fit_enum = [](symbol::type_t t)
	{
		using e1 = symbol::type_t;
		using e2 = sparge::symbol::type_t;
		switch (t)
		{
		case e1::Nonterminal : return e2::nonterminal ;
		case e1::Terminal 	 : return e2::terminal 	  ;
		case e1::Noise 		 : return e2::noise 	  ;
		case e1::EndOfFile 	 : return e2::end_of_file ;
		case e1::GroupStart  : return e2::group_start ;
		case e1::GroupEnd 	 : return e2::group_end   ;
		case e1::Decrement 	 : return e2::decrement   ;
		case e1::Error		 : return e2::error		  ;
		default :
			std::cerr << "error in file, corrupted symbol table" << std::endl;
			std::exit(1);
		}
	};

	auto filter_name = [](std::u32string & s)
	{

		if (s == U"EOF")
		{
			s = U"end_of_file";
			return;
		}

		if ((s[0] >= U'0') && (s[0] <= U'9'))
			s.insert(0, 1, U'_');

		for (auto i = 0u; i != s.size(); i++)
		{
			char32_t c = s[i];
			if (c == U' ')
			{
				s[i] = '_';
			}
			else if (
					((c < U'A') || (c > U'Z'))
				&& 	((c < U'a') || (c > U'z'))
				&&  ((c < U'1') || (c > U'0'))
				&&  (c != U'_'))
			{
				s.erase(i);
				auto t = boost::lexical_cast<std::u32string>(static_cast<int>(c));
				s.insert(i, U"u" + t);
				i += t.size();
			}
		}
	};

	auto transform_symbol  = [&](const symbol & s)
	{
		auto nm = utf_to_utf<char32_t, char16_t>(s.name);
		filter_name(nm);

		sparge::symbol ret;
		ret.type = fit_enum(s.type);
		ret.name = nm;
		return ret;
	};

	auto l = [&](const std::pair<integer, symbol> & s)
		{
			return std::pair<int, sparge::symbol>
					{
						s.first,
						transform_symbol(s.second)
					};
		};

	std::transform(f.symbol_table.begin(), f.symbol_table.end(),
			std::inserter(p.symbols, p.symbols.end()) , l);



}

void transform_grp (sparge::parser &p, const file &f)
{
	auto l = [&](const std::pair<integer, group_record> & g)
		{
			sparge::token_group tg;
			const group_record & gg = g.second;

			tg.advange_mode = (gg.advance_mode == group_record::Token) ?
							   sparge::token_group::token
							 :  sparge::token_group::character;

			tg.ending_mode = (gg.ending_mode == group_record::Open) ?
							   sparge::token_group::open
							 : sparge::token_group::closed;

			tg.container = gg.container_index;
			tg.start 	 = gg.start_index ;
			tg.end		 = gg.end_index;

			tg.name = boost::locale::conv::utf_to_utf<char32_t, char16_t>(
								reinterpret_cast<const char16_t *>(&*gg.name.begin()),
								reinterpret_cast<const char16_t *>(&*gg.name.end()));


			return std::pair<int, sparge::token_group> {g.first, tg};

		};


	std::transform(f.group_records.begin(), f.group_records.end(),
			std::inserter(p.token_groups, p.token_groups.end()) , l);
}


void transform_prod (sparge::parser &p, const file &f)
{



	auto l = [&](const std::pair<std::uint16_t, production> & l)
	{
		sparge::production l_out;

		l_out.head_index = l.second.head_index;
		std::copy(l.second.symbols.begin(), l.second.symbols.end(),
				std::back_inserter(l_out.symbols));

		return  std::pair<int, sparge::production>{l.first,  l_out};
	};

	std::transform(f.productions.begin(), f.productions.end(),
			std::inserter(p.productions, p.productions.end()) , l);
}

void transform_lalr (sparge::parser &p, const file &f)
{

	auto tr_action = [](const lalr_state::action_t & a)
	{
		sparge::lalr_state::action a_out;

		a_out.symbol_index = a.symbol_index;
		a_out.target = a.target_index;

		switch (a.action)
		{
		case lalr_state::Shift	: a_out.action = sparge::lalr_state::shift	; break;
		case lalr_state::Reduce : a_out.action = sparge::lalr_state::reduce; break;
		case lalr_state::Goto	: a_out.action = sparge::lalr_state::goto_	; break;
		case lalr_state::Accept : a_out.action = sparge::lalr_state::accept; break;
		}
		return a_out;
	};


	auto l = [&](const std::pair<std::uint16_t, lalr_state> & l)
	{
		sparge::lalr_state l_out;

		std::transform(l.second.actions.begin(), l.second.actions.end(),
				std::back_inserter(l_out.actions),	tr_action);

		return  std::pair<int, sparge::lalr_state>{l.first,  l_out};
	};

	std::transform(f.lalr_states.begin(), f.lalr_states.end(),
			std::inserter(p.lalr_states, p.lalr_states.end()) , l);
}

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

	transform_sym(p, f);
	transform_dfa(p, f);
	transform_grp(p, f);


	transform_prod(p, f);
	transform_lalr(p, f);

	return p;

}

}
}
