#include"stdafx.h"
#include "Instruction.h"
#include "Errors.h"

/**/
/*
 Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
 NAME
	ParseInstruction(string &a_buff)

 SYNOPSIS
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
	a_buff --> The original statement to be parsed

 DESCRIPTION
	This function checks if the opCode is a machine language, assembly language, comment
		or an end instruction.

 RETURN
	The enum type of instruction (ST_MachineLanguage, ST_AssemblerInstr, ST_Comment or ST_End)
*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	//Make a copy of the original instruction
	m_instruction = a_buff;

	//Get rid of everything after the semicolon if it exists.
	size_t isemi = 0;
	isemi = a_buff.find(';');
	if (isemi != string::npos) {
		a_buff = a_buff.substr(0, isemi);
	}

	//Parse Instruction into basic elements
	GetLabelOpcodeEtc(a_buff);

	//transform all machine OpCodes into lowercase letters
	std::transform(m_OpCode.begin(), m_OpCode.end(), m_OpCode.begin(), tolower);

	//Check if the OpCode is a Machine Language
	if (find(quack_OpCode.begin(), quack_OpCode.end(), m_OpCode) != quack_OpCode.end()) {
		m_type = ST_MachineLanguage;

		//Find the numeric equivalent of the OpCode which is written in order in the Vector
		m_NumOpCode = distance(quack_OpCode.begin(), find(quack_OpCode.begin(), quack_OpCode.end(), m_OpCode)) + 1;
	}

	//Check if the OpCode is an Assembly Language
	else if (find(assembly_OpCode.begin(),assembly_OpCode.end(),m_OpCode) != assembly_OpCode.end()) {
		m_type = ST_AssemblerInstr;
	}

	//Check if the OpCode is the end of the input file
	else if (m_OpCode == "end") {
		m_type = ST_End;
	}

	//Declare none if OpCode doesn't match any of the above
	else {
		m_type = ST_Comment;
	}
	
	//Convert the Operand to Numeric Value to trace location
	try {
		m_OperandValue = stoi(m_Operand);
		m_IsNumericOperand = true;
	}
	catch(invalid_argument) {
		m_IsNumericOperand = false;
	}
	//Return the InstructionType
	return m_type;
}/*Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)*/

/**/
/*
 void Instruction::GetLabelOpcodeEtc(const string &a_buff)
 NAME
	GetLabelOpcodeEtc(const string &a_buff)

 SYNOPSIS
	void Instruction::GetLabelOpcodeEtc(const string &a_buff)
	a_buff --> The statement which contains the label, opcode and operand

 DESCRIPTION
	This function identifies the label, opcode and operand. It also determines the numerical
	value of opCode, Operand and Label.

 RETURN
	void
*/
/**/

void Instruction::GetLabelOpcodeEtc(const string &a_buff) {
	m_Label = m_OpCode = m_Register = m_Operand = "";
	istringstream ins(a_buff);

	string a1, a2, a3, a4;
	ins >> a1 >> a2 >> a3 >> a4;

	//Assign values for strings a1-a4
	if (a_buff[0] != ' ' && a_buff[0] != '\t') { // '\t' = tab
		m_Label = a1;
		m_OpCode = a2;
		m_Operand = a3;
		if (a4 != "") {
			Errors::RecordError("Invalid Instruction in the Text file!");
		}
	}
	else {
		m_OpCode = a1;
		m_Operand = a2;
		if (a3 != "") {
			Errors::RecordError("Invalid Instruction in the Text file!");
		}
	}
	// Check operand for comma and parse accordingly 
	size_t icomma = m_Operand.find(',');
	if (icomma != string::npos)
	{
		m_Register = m_Operand.substr(0, icomma);
		m_NumRegister = stoi(m_Register);
		m_Operand = m_Operand.substr(icomma + 1);
	}
	else
	{
		m_Register = "9";
		m_NumRegister = stoi(m_Register);
	}
	
}/*void Instruction::GetLabelOpcodeEtc(const string &a_buff)*/

/**/
/*
int Instruction::LocationNextInstruction(int a_loc)
 NAME
	LocationNextInstruction(int a_loc)

 SYNOPSIS
	int Instruction::LocationNextInstruction(int a_loc)
	a_loc--> Current Location

 DESCRIPTION
	This function identifies next location by taking in a parameter of the current location.

 RETURN
	Location of Next Instruction
*/
/**/

int Instruction::LocationNextInstruction(int a_loc) {
	if (m_OpCode == "org"  || m_OpCode == "ds") {
		return a_loc + m_OperandValue;
	}
	return a_loc + 1;
}/*int Instruction::LocationNextInstruction(int a_loc)*/