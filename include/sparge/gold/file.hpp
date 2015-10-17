/*
 * File.h
 *
 *  Created on: 23.04.2015
 *      Author: Klemens
 */

#ifndef SPARGE_GOLD_FILE_H_
#define SPARGE_GOLD_FILE_H_

#include <sparge/gold/reader/raw_file.hpp>
#include <sparge/gold/types.hpp>
#include <sparge/gold/property.hpp>
#include <sparge/gold/table_counts.hpp>
#include <sparge/gold/character_set_table.hpp>
#include <sparge/gold/symbol.hpp>
#include <sparge/gold/group.hpp>
#include <sparge/gold/production.hpp>
#include <sparge/gold/initial_states.hpp>
#include <sparge/gold/dfa_state.hpp>
#include <sparge/gold/lalr_state.hpp>
#include <ostream>

namespace sparge {
namespace gold {

struct file
{
	string gold_version 	;
	string name				;
	string version			;
	string author			;
	string about			;
	string character_set	;
	string character_mapping;
	string generated_by		;
	string generated_date 	;

	table_counts table_counts;
	map<character_set_table> character_set_tables;
	map<symbol> symbol_table;
	map<group_record> group_records;
	map<production> productions;

	initial_states initial_states;

	map<dfa_state> dfa_states;
	map<lalr_state> lalr_states;

	void add_property(const property &prop);
	void add_record(const record &r);

};

file read_raw_file(const std::string & rf);
file read_raw_file(const raw_file & rf);

std::ostream & operator<<(std::ostream & ostr, const file &f);

}}

#endif /* SPARGE_GOLD_FILE_H_ */
