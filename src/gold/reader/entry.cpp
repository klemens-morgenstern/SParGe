
#include <sparge/gold/reader/entry.hpp>
#include <sstream>
#include <locale>
#include <boost/locale/encoding.hpp>

using namespace std;

namespace sparge
{
namespace gold
{

struct visi : boost::static_visitor<std::string>
{
	std::string operator()(boost::none_t) {return "blank";}
	std::string operator()(char val)
	{
		ostringstream ws;
		ws << "byte: " << val;
		return ws.str();
	}
	std::string operator()(bool val)
	{
		ostringstream ws;
		ws << "bool: " << val;
		return ws.str();

	}
	std::string operator()(char16_t val)
	{
		ostringstream ws;
		ws << "int: " << val;
		return ws.str();

	}
	std::string operator()(std::u16string  val)
	{
		std::string st = boost::locale::conv::from_utf(val, std::locale().name());
		return "string: " + st + "\n";
	}
};


ostream &operator<<(ostream& str, const entry &e)
{
	visi v;
	str << "\t" <<  e.data.apply_visitor(v) << endl;


	return str;
}




entry entry::read_entry(std::istream& str)
{
	char c = str.peek();


	switch(c)
	{
	case 'E': //empty
		str.read(&c, 1);
		return {};
	case 'b': //bool
	{
		str.read(&c, 1);
		str.read(&c, 1);
		return entry(c);
	}
	case 'B': //bool
	{
		str.read(&c, 1);
		str.read(&c, 1);
		return entry(c != 0);
	}
	case 'I': //Integer
	{
		str.read(&c, 1);
		char16_t val;
		str.read(reinterpret_cast<char*>(&val), 2);
		return entry(val);
	}
	case 'S':
	{
		str.read(&c, 1);
		return entry(read_string(str));
	}
	default:
		throw std::runtime_error("Load error in entry - ");
		return entry();
	}
}



}}
