// TemperatureChecks.h

#ifndef _TEMPERATURECHECKS_h
#define _TEMPERATURECHECKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DallasTemperature.h>
#include "DefinedValues.h"
#include "Enums.h"

OneWire ds18x20[] = { TEMP_IN_ID, TEMP_OUT_ID };
const int oneWireCount = sizeof(ds18x20)/sizeof(OneWire);

class TemperatureChecksClass
{
 protected:
static DallasTemperature sensor[oneWireCount];
static float _last_temps[2];

 public:
static	void init();
static float GetTemp(int inOut);
static  IsOn(int inOut);
};

extern TemperatureChecksClass TemperatureChecks;

#endif

