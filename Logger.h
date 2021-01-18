// Logger.h

#ifndef _LOGGER_h
#define _LOGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Enums.h"
#include "Json.h"
#include "Log.h"
#include "LCD.h"
#include "RTClib.h"
#include "SDCard.h"
class LoggerClass
{
	// called as simple function

public:
	static void LoggerClass::Init();
	static String LogEntry();
private:
	static String DisplayLCDLines();
};

extern LoggerClass Logger;

#endif

