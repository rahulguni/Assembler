//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Errors.h"
#include "Assembler.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler()
{
}

/**/
/*
 void Assembler::PassI()
 NAME
	Assembler::PassI()

 SYNOPSIS
	void Assembler::PassI()

 DESCRIPTION
	This function parses the assembly code and establishes the location of the labels.
	Then it adds the symbol with their respective addresses to the symbol table and displays it.

 RETURN
	void
*/
/**/

void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string line;
		if (!m_facc.GetNextLine(line)) {
			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}/*void Assembler::PassI()*/

/**/
/*
 void Assembler::PassII()
 NAME
	Assembler::PassII()

 SYNOPSIS
	void Assembler::PassII()

 DESCRIPTION
	This function parses the assembly code and prints out the translation of the program required
	for the emulator, containing the location and contents of the instruction.

 RETURN
	void
*/
/**/

void Assembler::PassII() {
	//first re-read the file to parse the instructions
	m_facc.rewind();

	int loc = 0;			// Tracks the location of the labels recorded in Pass I.
	string ErrMsg = "";		// To record error messeges

	//Output headers of this program
	cout << "\t Translation of the Program:" << endl << endl;
	cout << "Location" << setw(12) << "Contents" << left << "\t Original Statement" << endl;
	
	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {
			// If there are no more lines, we are missing an end statement.
			ErrMsg = "No END statement at the end of file!";
			Errors::RecordError(ErrMsg);
			//Reset the ErrMsg string
			ErrMsg.clear();
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		//Determine if the instruction type is a comment and print it out
		if (st == Instruction::ST_Comment) {
			cout << "\t \t \t" << m_inst.GetInstruction() << endl;
			continue;
		}

		//Determine if END is the last statement
		if (st == Instruction::ST_End) {
			cout << "\t \t \t" << m_inst.GetInstruction() << endl;
			return;
		}

		//Error Report: Illegal Label format
		if (isdigit(m_inst.GetLabel()[0])) {
			ErrMsg = m_inst.GetLabel() + ":Label starts with a number.Illegal.";
			Errors::RecordError(ErrMsg);
			ErrMsg.clear();
		}

		//Error Report: Labels cannot be very long
		if (m_inst.GetLabel().length() > 5) {
			ErrMsg = m_inst.GetLabel() + ":Label too long. Keep it les than 5 characters.";
			Errors::RecordError(ErrMsg);
			ErrMsg.clear();
		}

		//Error Report: If memory address exceeds 100,000 which is the size of this computer
		if (m_inst.isOperand()) {
			if (m_inst.GetNumericOp() > 100000) {
				ErrMsg = "The numeric value of Operand is too high: " + m_inst.GetOperand();
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}
		}

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}

		int numCode, regValue, t_loc;	//for the numeric opCode value and register values
		int temp_cont;					//for the numeric value of contents before converting into string
		temp_cont = numCode = regValue = t_loc = 0;

		//compute values for numCode and regValues to add it to temp_cont later
		numCode = m_inst.GetNumOpCode();
		regValue = m_inst.GetRegValue();

		//Determine if the OpCode is an assembly Language Instruction
		if (st == Instruction::ST_AssemblerInstr) {

			//check if the operand is empty
			if (m_inst.GetOperand().empty()) {
				ErrMsg = "Operand not found!";
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}

			/*check for errors in operand and opcode (operand of an assembly language 
			must be numeric)*/
			else if (!m_inst.isOperand()) {
				ErrMsg = m_inst.GetOperand() + " :Illegal.Operand needs to be numeric.";
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}

			//Report error for empty labels if the opcode is not "org"
			else if ((m_inst.GetOpCode() != "org" && m_inst.GetLabel().empty())) {
				ErrMsg = "No Operand found!";
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}
			else {
				if (m_inst.GetOpCode() == "dc") {
					numCode = 0;
					regValue = 0;
					temp_cont = m_inst.GetNumericOp();
				}

				else {
					temp_cont = 0;
				}
			}
		}

		//If the OpCode is not an assembly language, comment or end Instructions, it is a Machine Language
		//Determine the contents for a machine language instructions
		else {

			//Report error if no operand found for instruction except for HALT.
			if (m_inst.GetOperand() == "" && m_inst.GetNumOpCode() != 13)
			{
				ErrMsg = m_inst.GetOpCode() + " :Illegal. Operand missing in opcode!";
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}

			//Report error if operand is a number instead of a symbol
			if (m_inst.isOperand()) {
				ErrMsg = m_inst.GetOperand() + ": Illegal. Operand must be a symbol, not a number.";
				Errors::RecordError(ErrMsg);
				ErrMsg.clear();
			}

			if (m_inst.GetOperand() != "") {
				//Make sure the operand is present in the symbol table with a location
				if (m_symtab.LookupSymbol(m_inst.GetOperand(), t_loc)) {
					temp_cont = numCode * 1000000 + regValue * 100000 + t_loc;
				}
				else {
					//Report error for missing symbol in the symbol table.
					ErrMsg = "Symbol " + m_inst.GetOperand() + " not found in the symbol table.";
					Errors::RecordError(ErrMsg);
					ErrMsg.clear();
				}
			}

			else {
				//for instruction such as halt where there is no operand
				temp_cont = numCode * 1000000 + regValue * 100000;
			}
		}

		//record the contents in the emulator
		m_emul.insertMemory(loc, temp_cont);

		string contents; //to print out contents in the correct order (8 digits)

		//print nothing in contents if it is a null
		if (temp_cont == 0) {
			contents = "";
		}

		//Insert 0s infront of contents to ensure it is of 8-digits
		else {
			contents = string(8 - to_string(temp_cont).length(), '0') + to_string(temp_cont);
		}
		//Output of this program
		cout << right << setw(5) << loc << right << setw(13) << contents << "\t  " << m_inst.GetInstruction() << endl;

		//display errors if there is error reading the instructions
		Errors::DisplayErrors();

		//clear all the errors
		Errors::InitErrorReporting();

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}/*void Assembler::PassII()*/

void Assembler::DisplaySymbolTable() {
	m_symtab.DisplaySymbolTable();
}

/**/
/*
 void Assembler::RunProgramInEmulator()
 NAME
	Assembler::RunProgramInEmulator()

 SYNOPSIS
	void Assembler::RunProgramInEmulator()

 DESCRIPTION
	This function first checks for errors and if no error found, runs the emulator

 RETURN
	void
*/
/**/

void Assembler::RunProgramInEmulator() {
	if (!Errors::CheckError()) {
		cout << "Emulator cannot run because of errors." << endl;
	}
	else {
		m_emul.runProgram();
	}
}/*void Assembler::RunProgramInEmulator()*/
