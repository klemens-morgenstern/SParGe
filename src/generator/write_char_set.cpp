/**
 * @file   write_char_set.cpp
 * @date   23.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */


#include <sparge/generator.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace sparge
{

std::vector<std::string> encs
{
	"cp1250"   ,
	"cp1251"   ,
	"cp1252"   ,
	"cp1253"   ,
	"cp1254"   ,
	"cp1255"   ,
	"cp1256"   ,
	"cp1257"   ,
	"cp874"    ,
	"cp932"    ,
	"cp936"    ,
	"eucjp"    ,
	"euckr"    ,
	"gb18030"  ,
	"gb2312"   ,
	"gbk"      ,
	"iso88591" ,
	"iso88592" ,
	"iso88593" ,
	"iso88594" ,
	"iso88595" ,
	"iso88596" ,
	"iso88597" ,
	"iso88598" ,
	"iso88599" ,
	"iso885913",
	"iso885915",
	"usascii" ,
	"utf8"    ,
};

void generator::write_char_set() const
{
	std::string cs {
		"template<int Index, encoding Encoding>\n"
		"struct {} char_set;\n"
	};



	auto enum_f = boost::format("\t%1%,\n");

	auto out = path / "char_sets.hpp";

    std::ofstream ofs(out.string());

    boost::format include_f{ "#ifndef %1%\n#define %1%\n\n\n"};
    ofs << include_f % (include_guard + "CHAR_SETS_H_");

    ofs << "\n#include <array>\n\n";
   // ofs << "#include <" << path.string() << "/symbols.hpp" << ">\n\n";
    ofs << ns_in;

    //write the encoding enum
    {
    	ofs << "\nenum class encoding\n{\n";
    	for (auto & e : encs)
    		ofs << enum_f % e;
    	ofs << enum_f % "utf16";//cause it's not 8-bit encoding.
    	ofs << enum_f % "utf32";
    	ofs << "};\n\n";
    }
    ofs << cs << "\n";

    auto cs_f   = boost::format(
    			"template<> constexpr static"
    			"\tstd::array<%1%, %2%> char_set<%3%, encoding::%4%> "
    			"\t{ %5% };\n");

    //now the format char sets.
    for (const std::pair<const int, char_set> & cs : data.char_sets)
    {
    	for (auto & e : encs)
    	{
    		auto cs_conv = boost::locale::conv::from_utf(
    				&*cs.second.char_set.begin(),
					&*cs.second.char_set.end(), e);

    		std::stringstream ss;
    		for (auto & c : cs_conv)
    			ss << static_cast<int>(c) << ", ";

    		ofs << cs_f % "char" % cs_conv.size() % cs.first % e % ss.str();
    	}

    	auto utf16 = boost::locale::conv::utf_to_utf<char16_t, char32_t>(
								&*cs.second.char_set.begin(),
								&*cs.second.char_set.end());

    	std::stringstream s16;
    	for (auto & c : utf16)
    		s16 << static_cast<int>(c) << ", ";

    	ofs << cs_f % "char16_t" % utf16.size() % cs.first % "utf16" % s16.str();

    	std::stringstream s32;
    	for (auto & c : cs.second.char_set)
    		s32 << static_cast<int>(c) << ", ";

    	ofs << cs_f % "char32_t" % cs.second.char_set.size() % cs.first % "utf32" % s32.str();



    }

    ofs << ns_out;
    ofs << "\n\n#endif\n";
}

}


