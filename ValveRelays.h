// ValveRelays.h

#ifndef _VALVERELAYS_h
#define _VALVERELAYS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DefinedValues.h"
#include "Statics.h"
class ValveRelaysClass
{
private:
public:
	static void Init();
	static int* GetPins(int valveSet);
	static void SetValvePinsToOutput(int valveSet);
	static int TurnOnAllValves(int valveSet);
	static int TurnOffAllValves(int valveSet);
	static void CloseValve(int valveSet,int lineNumber);
	static void OpenValve(int valveSet,int lineNumber);
};

extern ValveRelaysClass ValveRelays;

#endif

