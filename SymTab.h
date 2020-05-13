//
//		Symbol table class.
//
#pragma once
/**/
/*
	NAME
		class SymbolTable

	DESCRIPTION
		This class contains all the necessary functions to maintain a table of symbols and their addresses.
		Add Symbol --> Adds symbol to the symbol table
		Display Symbol -- > Displays the symbol and its corresponding locations in the table
*/
/**/
#include<string>
#include "stdafx.h"


// This class is our symbol table.
class SymbolTable {

public:
	// Get rid of constructor and destructor if you don't need them.
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol, int &a_loc);

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;
};
