// stdafx.cpp : source file that includes just the standard includes
// assem.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

/**/
/*
NAME
	PressEnter - Just for the sake of a good output

SYNOPSIS
	void PressEnter();

DESCRIPTION
	To have the option of pressing enter key after each translation for a better output.

RETURN
	void
*/
/**/

void PressEnter() {
	cout << endl;
	cout << "______________________________________________________" << endl << endl;
	cout << "Press ENTER to continue: ";
	cin.ignore();
	cout << endl << endl;
}/*void PressEnter()*/