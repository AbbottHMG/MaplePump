// SapLine.h

#ifndef _SAPLINE_h
#define _SAPLINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ValveRelays.h"
#include "Vacuum.h"
class SapLineClass
{
 protected:
 public:
	 bool IsLineOk();
	 unsigned long TimeLineFailed();
	 unsigned long TimePriorFailed();
	 void Init(int lineNumber);
	 void ShutMeOff();
	 void TurnMeOn();
	 bool IsOn();
	 bool IsOff();
};

extern SapLineClass SapLine;

#endif

