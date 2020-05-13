#include "stdafx.h"
#include "SymTab.h"

/**/
/*
 void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
 NAME
	AddSymbol - adds a new symbol to the symbol table.

 SYNOPSIS
	void SymbolTable::AddSymbol( char *a_symbol, int a_loc );
	a_symbol --> the symbol to be added to the table
	a_loc --> the symbol's corresponding location to be added to the table

 DESCRIPTION
	This function will place the symbol "a_symbol" and its location "a_loc"
	in the symbol table.

 RETURN
	void
*/
/**/

void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}/*void SymbolTable::AddSymbol(string &a_symbol, int a_loc)*/

/**/
/*
 void SymbolTable::DisplaySymbolTable()
 NAME
	DisplaySymbolTable - Displays the Symbol Table

 SYNOPSIS
	void SymbolTable::DisplaySymbolTable();

 DESCRIPTION
	This function will display the symbol number, symbol and its location
	in the symbol table in the format-
	            Symbol #   Symbol   Location

 RETURN
	void
*/
/**/

void SymbolTable::DisplaySymbolTable() {
	int num = 0;
	cout << "Symbol#" << setw(8) << "Symbol" << setw(10) << "Location" << endl;
	map<string, int>::iterator it;
	for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++) {
		cout << setw(2) << num++ << setw(10) << it->first << setw(10) << it->second << endl;
	}
}/*void SymbolTable::DisplaySymbolTable() */

/**/
/*
 bool SymbolTable:: LookupSymbol(string &a_symbol, int &a_loc)
 NAME
	LookupSymbol- Finds symbol in the symbol table

 SYNOPSIS
	bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
	a_symbol --> The Symbol to look up
	a_loc --> If the symbol is found place the symbol's location in a_loc

 DESCRIPTION
	Looks up if a symbol exists in the symbol table.

 RETURN
	TRUE if symbol exists, else FALSE
*/
/**/

bool SymbolTable:: LookupSymbol(string &a_symbol, int &a_loc) {
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end()) {
		return false;
	}
	// Record the location of the symbol in a_loc
	a_loc = m_symbolTable[a_symbol];
	return true;
}/*bool SymbolTable:: LookupSymbol(string &a_symbol, int &a_loc)*/
