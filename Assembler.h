//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

/**/
/*
	NAME
		class Assembler

	DESCRIPTION
		This class contains all the necessary functions to build the assembler
		Pass I  ---> Establishes the location of symbols
		Pass II ---> Generates the Translation
		Display Table ---> Displays the Symbol Table.
*/
/**/

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"

class Assembler {

public:
	Assembler(int argc, char *argv[]);
	~Assembler();

	// Pass I - establish the locations of the symbols
	void PassI();

	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable();

	// Run emulator on the translation.
	void RunProgramInEmulator();

private:

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab; // Symbol table object
	Instruction m_inst;	    // Instruction object
	Emulator m_emul;        // Emulator object
};

