// TempCheck.h

#ifndef _TEMPCHECK_h
#define _TEMPCHECK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DefinedValues.h"
#include "Log.h"
#include "Enms.h"
#include <DallasTemperature.h>
#include <OneWire.h>
class TempCheckClass
{
private:
	static float GetTemp(int sensorId);
public:
	static void Init();
	static EnumsClass::Temperature GetInState();
	static EnumsClass::Temperature GetLastOutState();
	static EnumsClass::Temperature GetOutState();
	static float GetTempFloat(int sensorId);
	static String GetTempStr(int sensorId);
	static bool IsTempLow();
	static void SetTempStates(bool init);
};

extern TempCheckClass TempCheck;

#endif

