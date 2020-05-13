#include "Emulator.h"
#include "stdafx.h"
#include "Errors.h"

/**/
/*
 bool Emulator::insertMemory(int a_location, int a_contents)
 NAME
	insertMemory(int a_location, int a_contents)

 SYNOPSIS
	Emulator::insertMemory(int a_location, int a_contents)
	a_location --> The location of symbol
	a_contents --> The contents to translate after pass II

 DESCRIPTION
	This function puts the contents and locations obtained from Pass II in the memory of Quack3200.

 RETURN
	True if contents are successfully stored in the specified location, else false.
*/
/**/

bool Emulator::insertMemory(int a_location, int a_contents)
{
	// Check if the location exceeds 100,000 words in memory
	// Also, record the error
	if (a_location >= 0 && a_location < MEMSZ) {
		//record data in memory
		m_memory[a_location] = a_contents;
		return true;
	}
	else {
		Errors::RecordError("Cannot insert into the emulator because memory size is too small for the location.");
		return false;
	}
}//bool Emulator::insertMemory(int a_location, int a_contents)


/**/
/*
 bool Emulator::runProgram()
 NAME
	runProgram()

 SYNOPSIS
	bool Emulator::runProgram()

 DESCRIPTION
	This function extracts the OpCode, Address and Register value from the memory and operates
	differently according to the OpCode. The first two digits stored in a location in the memory
	acts as OpCode, third as register value and the last five as addresses.

 RETURN
	True if contents are successfully stored in the specified location, else false.
*/
/**/

bool Emulator::runProgram()
{
	int opCode = 0;
	int input = 0;
	int address = 0;
	int reg = 0;

	for (int loc = 0; loc < MEMSZ; loc++)
	{
		int contents = m_memory[loc];
		//emulate only if memory has contents
		if (contents != 0)
		{
			opCode = contents / 1000000;	//get the first two digits for opcode
			address = contents % 10000;		//get the last four digits for address
			reg = (contents / 100000) % 10; //get the thirs digit for register number

			switch (opCode)
			{
			case 1:
				// ACC <-- content(ACC) + c(ADDR)
				m_reg[reg] += m_memory[address];
				break;

			case 2:
				// ACC <-- content(ACC) - c(ADDR)
				m_reg[reg] -= m_memory[address];
				break;

			case 3:
				// ACC <--content(ACC) * c(ADDR)
				m_reg[reg] *= m_memory[address];
				break;

			case 4:
				// ACC <--content(ACC) / c(ADDR)
				m_reg[reg] /= m_memory[address];
				break;

			case 5:
				// ACC <--c(ADDR)
				m_reg[reg] = m_memory[address];
				break;

			case 6:
				// ADDR<--c(ACC)
				m_memory[address] = m_reg[reg];
				break;

			case 7:
				// A line is read and its first 6 digits are
				// placed in the specified address. Register value is ignored.
				cout << "?";
				cin >> input;
				input %= 1000000;
				m_memory[address] = input;
				break;

			case 8:
				// c(ADDR) is displayed
				cout << m_memory[address] << endl;
				break;

			case 9:
				// Go to ADDR for next instruction
				loc = address;
				break;

			case 10:
				// Go to ADDR if c(ACC) < 0
				if (m_reg[reg] < 0)
				{
					loc = address - 1;
				}
				break;

			case 11:
				// Go to ADDR if c(ACC) = 0
				if (m_reg[reg] == 0)
				{
					loc = address - 1;
				}
				break;

			case 12:
				// Go to ADDR if c(ACC) > 0
				if (m_reg[reg] > 0)
				{
					loc = address - 1;
				}
				break;

			case 13:
				// Terminate execution
				loc = 1000000;
				break;
			}
		}
	}
	return false;
}//bool Emulator::runProgram()

