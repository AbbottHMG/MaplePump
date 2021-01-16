// FlowMeter.h

#ifndef _FLOWMETER_h
#define _FLOWMETER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DefinedValues.h"
#include "Statics.h"
#include "log.h"

class FlowMeterClass
{
private:
	//Insterrupt Service Routine

	static void pulseCounter();

public:
	static float FlowRate();
	static void Init();
	static void ProcessSlice();
};

extern FlowMeterClass FlowMeter;

#endif

