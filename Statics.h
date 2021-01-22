// Statics.h

#ifndef _STATICS_h
#define _STATICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class StaticsClass
{

public:
	static void ClearCharArray(String array);
	static void CopyInts(int* from, int* to, int count);
	static bool CopyChars(char* from, char* to);
	static bool CopyChars(String from, String to, int length);
	static String IntArrayToString(int* array);
	static char* StringToCharArray(String string);
	static void Delay(unsigned long waitTime);
};


extern StaticsClass Statics;

#endif

