// VacuumPump.h

#ifndef _VACUUMPUMP_h
#define _VACUUMPUMP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class VacuumPumpClass
{
private:
	static void CompleteBypass();
	static void OpenPumpValve();
	static void StopBypass();
	static void StartBypass();
 public:
	static void CheckPumpFlow();
	static void Init();
	static bool IsOff();
	static bool IsOn();
	static void TurnOff();
	static void TurnOn();
};

extern VacuumPumpClass VacuumPump;

#endif

