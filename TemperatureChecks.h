// TemperatureChecks.h

#ifndef _TEMPERATURECHECKS_h
#define _TEMPERATURECHECKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DallasTemperature.h>
#include <OneWire.h>
#include "DefinedValues.h"
#include "Enums.h"

static OneWire oneWires[] = { TEMP_IN_ID, TEMP_OUT_ID };
static const int oneWireCount = sizeof(oneWires)/sizeof(OneWire);

class TemperatureChecksClass
{
 protected:
static DallasTemperature sensor[oneWireCount];
static float _last_temps[2];

 public:
static	void init();
static float GetTemp(int inOut);
static bool IsInRange(int inOut);
};

extern TemperatureChecksClass TemperatureChecks;

#endif

