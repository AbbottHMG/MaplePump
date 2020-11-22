// Log.h

#ifndef _LOG_h
#define _LOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "RTClock.h"
#include "DefinedValues.h"
class LogClass
{
public:
	static void Init();
	static String Action(String value = "");
	static String ActiveLines(String value = "");
	static String BrokenLines(String value = "");
	static String Date();
	static String FileName(String value = "");
	static String FlowLast(String value = "");
	static String FlowRate(String value = "");
	static String FlowTot(String value = "");
	static String FreeRam(String value = "");
	static String InTempF(String value = "");
	static String JsonLen(String value = "");
	static String OutTempF(String value = "");
	static String SapPump(String value = "");
	static String State(String value = "");
	static String VacuumPsi(String value = "");
	static String WebAction(String value = "");
	static String WebMessage(String value = "");
	static String WebRequest(String value = "");
};

extern LogClass Log;


#endif
