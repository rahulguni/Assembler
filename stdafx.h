// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

/**/
/*
	NAME
		class stdafx

	DESCRIPTION
		This class contains all the necessary includes headers to build the assembler.
*/
/**/

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>

// Standard include files.
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

void PressEnter();
