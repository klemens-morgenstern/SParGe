
#ifndef SPARGE_GOLD_TABLECOUNTS_H_
#define SPARGE_GOLD_TABLECOUNTS_H_

#include <sparge/gold/types.hpp>
#include <ostream>

namespace sparge {
namespace gold {
struct record;

/** TableCounts
 * Byte: 't'/116
 * | Item				 |  Type   | Description												|
 * |---------------------|---------|------------------------------------------------------------|
 * | Symbol Table	     | Integer | The number of symbols in the language.                     |
 * | Character Set Table | Integer | The number of character sets used by the DFA state table.  |
 * | Rule Table	         | Integer | The number of rules/productions in the language.           |
 * | DFA Table	         | Integer | The number of Deterministic Finite Automata states.        |
 * | LALR Table	         | Integer | The number of LALR States.                                 |
 * | GroupTable	         | Integer | The number of lexical groups.                              |
 */
struct table_counts
{
	static constexpr byte id = 't';

	integer symbol_table;
	integer set_table;
	integer rule_table;
	integer dfa_table;
	integer lalr_table;
	integer group_table;

	static table_counts from_record(const record &r);

};

std::wostream &operator<<(std::wostream& str, const table_counts &e);


}}
#endif /* SPARGE_GOLD_TABLECOUNTS_H_ */
