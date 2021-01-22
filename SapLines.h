// SapLines.h

#ifndef _SAPLINES_h
#define _SAPLINES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Enums.h"
#include "DefinedValues.h"
#include "Log.h"
#include "Task.h"
#include "Vacuum.h"
#include "ValveRelays.h"
#include "SapLine.h"
#include "Statics.h"
class SapLinesClass
{
protected:
	static void SetLogLineStates();
	static String GetBrokenLines();
	static String GetActiveLines();
public:
	static void Init();
	static bool CheckALine(TaskClass* task);
	static void TurnOffAllLines();
	static void TurnOnAllLines();
	static int GetActiveLineCount();
};

extern SapLinesClass SapLines;

#endif

