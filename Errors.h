#pragma once
//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//

/**/
/*
	NAME
		class Errors

	DESCRIPTION
		This class contains all the necessary functions to report the errors found while translating
		Report Error --> Reports all errors in a static vector so that it can be accessed from anywhere
		Display Error --> Displays all the errors after each translation
		Initiate Error --> Clear the error msg vector
*/
/**/

#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>
using namespace std;

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message. This is a constant so that accidental changes to error objects are avoided 
	// while reporting errors.
	static void RecordError(const string a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	//Check if there are errors in the final Error msg vector after all the translation is done.
	static bool CheckError();

private:

	static vector<string> m_ErrorMsgs;		//To store error and clear it after each translation
	static vector<string> m_FinalErrorMsgs; //To store all the errors until the end
};
#endif
