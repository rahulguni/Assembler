//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

/**/
/*
 NAME
	class Instruction

 DESCRIPTION
	This class contains all the necessary functions to parse and provide information about
		the instructions.
	Parse Instruction --> Parse the line and return its enum type
	Locate Next Instruction --> Compute the location of next instruction to be parsed
	Get Label, Opcode and Operands --> Parses the instruction and extracts the Label,
		Opcode and Operand according to the format.
*/
/**/

#include "stdafx.h"
// The elements of an instruction.
class Instruction {

public:

	// Constructor of the Instruction class
	Instruction() {
		m_NumOpCode = -99;
		m_IsNumericOperand = true;
		m_OperandValue = 0;
		m_type = ST_Comment;
		quack_OpCode = { "add","sub","mult","div","load","store","read","write","b","bm","bz","bp","halt" };
		assembly_OpCode = { "dc","ds","org" };
	}

	~Instruction() { };

	/* Codes to indicate the type of instruction we are processing.  This is inside the class
	to determine the instruction type for each instruction after passing it in the ParseInstruction 
	Function in Instruction.cpp and later in Assembler.cpp*/
	enum InstructionType {
		ST_MachineLanguage, 		// A machine language instruction.
		ST_AssemblerInstr,  		// Assembler Language instruction.
		ST_Comment,          		// Comment or blank line
		ST_End                  	// end instruction.
	};
	// Parse the Instruction and return the InstructionType 
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel() {

		return m_Label;
	}

	// To determine if a label is blank.
	inline bool isLabel() {
		if (m_Label != "") {
			return true;
		}
		else {
			return false;
		}
	}

	// To access the numeric value of op code
	inline int &GetNumOpCode() {
		return m_NumOpCode;
	}

	// To access the op code
	inline string &GetOpCode() {
		return m_OpCode;
	}

	// To access the numeric equivalent of the operand
	inline int &GetNumericOp() {
		return m_OperandValue;
	}

	// To access the operand
	inline string &GetOperand() {
		return m_Operand;
	}

	// To access the instruction
	inline string &GetInstruction() {
		return m_instruction;
	}

	// To determine if an operand is numeric
	inline bool &isOperand() {
		return m_IsNumericOperand;
	}

	// To access the register value
	inline int &GetRegValue() {
		return m_NumRegister;
	}

private:

	void GetLabelOpcodeEtc(const string &a_buff);


	// The elemements of a instruction
	string m_Label;         // The label.
	string m_OpCode;        // The symbolic op code.
	string m_Register;      // The register value.
	string m_Operand;       // The operand.


	string m_instruction;   // The original instruction.

	// Derived values.
	int m_NumOpCode;        // The numerical value of the op code.
	int m_NumRegister;	    // the numberic value for the register.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;     // The value of the operand if it is numeric.

	vector<string> quack_OpCode;
	vector<string> assembly_OpCode;
};

