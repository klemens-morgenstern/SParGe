
#include <sparge/gold/reader/record.hpp>
#include <sparge/gold/symbol.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/format.hpp>

using namespace std;

namespace sparge
{
namespace gold
{

indexed<symbol> symbol::from_record(const record &r)
{
	symbol cs;

	auto idx 	= r.entries.at(1).get<integer>();
	cs.name 	= r.entries.at(2).get<string>();
	cs.type 	= static_cast<symbol::type_t>(r.entries.at(3).get<integer>());

	return {idx, cs};
}


std::ostream & operator<<(std::ostream & ostr, const symbol &f)
{
	auto e = [](symbol::type_t t)
	{
		using e = symbol::type_t;
		switch (t)
		{

		case e::Nonterminal : return "Nonterminal ";
		case e::Terminal 	: return "Terminal    ";
		case e::Noise 		: return "Noise       ";
		case e::EndOfFile 	: return "EndOfFile   ";
		case e::GroupStart  : return "GroupStart  ";
		case e::GroupEnd 	: return "GroupEnd 	  ";
		case e::Decrement 	: return "Decrement   ";
		case e::Error		: return "Error	      ";
		default:
			return "";
		};
	};


	ostr << " | " << e(f.type) << " | " << boost::locale::conv::from_utf(f.name, "utf-8") << " |\n";


	return ostr;
}


}
}

