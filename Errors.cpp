#include "stdafx.h"
#include "Errors.h"

//included to not get a linking error
vector<string> Errors::m_ErrorMsgs;
vector<string> Errors::m_FinalErrorMsgs;

/**/
/*
 void Errors:: InitErrorReporting()
 NAME
	InitErrorReporting()

 SYNOPSIS
	void Errors:: InitErrorReporting()

 DESCRIPTION
	Initiate the Error reporting and erase previous errors.

 RETURN
	Void.
*/
/**/

void Errors:: InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}/*void Errors:: InitErrorReporting()*/

/**/
/*
 void Errors::RecordError(string a_emsg)
 NAME
	RecordError(string a_emsg)

 SYNOPSIS
	void Errors::RecordError(string a_emsg)
	a_emsg --> Error message

 DESCRIPTION
	Records the error messages found during translation

 RETURN
	Void.
*/
/**/

void Errors::RecordError(string a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
	m_FinalErrorMsgs.push_back(a_emsg);
}/*void Errors::RecordError(string a_emsg)*/

/**/
/*
 void Errors::DisplayErrors()
 NAME
	Errors::DisplayErrors()

 SYNOPSIS
	void Errors::DisplayErrors()

 DESCRIPTION
	Displays the errors recorded during the translation.

 RETURN
	Void.
*/
/**/

void Errors::DisplayErrors() {
	for (vector<string>::iterator it = m_ErrorMsgs.begin(); it!= m_ErrorMsgs.end(); it++) {
		cout << "Error --> " << *it << endl;
	}
}/*void Errors::DisplayErrors()*/

/**/
/*
 bool Errors::CheckError()
 NAME
	Errors::CheckError()

 SYNOPSIS
	bool Errors::CheckError()

 DESCRIPTION
	Checks for errors in the final error msg vector

 RETURN
	True if no error reported, else false.
*/
/**/

bool Errors::CheckError() {
	return m_FinalErrorMsgs.empty();
}/*bool Errors::CheckError()*/
