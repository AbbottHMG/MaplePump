// Json.h

#ifndef _JSON_h
#define _JSON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#include "DefinedValues.h"
#include "Enms.h"
#include "Log.h"
class JsonClass
{
public:
	static String BuildJsonDoc();
};

extern JsonClass Json;

#endif

