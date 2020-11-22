// Heater.h

#ifndef _HEATER_h
#define _HEATER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif 
#include"DefinedValues.h"
class HeaterClass {
private:
	static void TurnHeaterOff();
	static void TurnHeaterOn();
public:
	static void Init();
	static bool IsHeaterOff();
	static bool IsHeaterOn();
	static void SetHeater(bool setOn);
};
extern HeaterClass Heater;
#endif

