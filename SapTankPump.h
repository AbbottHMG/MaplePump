// SapTankPump.h

#ifndef _SAPTANKPUMP_h
#define _SAPTANKPUMP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DefinedValues.h"
#include "Statics.h"
#include "log.h"
#include "Logger.h"
class SapTankPumpClass{
public:
	static void Init();
	static bool IsTankPumpOff();
	static bool IsTankPumpOn();
	static void TurnTankPumpOn();
	static void TurnTankPumpOff();
};

extern SapTankPumpClass SapTankPump;

#endif

