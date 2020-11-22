// RTClock.h

#ifndef _RTCLOCK_h
#define _RTCLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <RTClib.h>

class RTClockClass
{
public:
	static bool isInitialized(bool setInitialized);
	static void Init();
	static bool IsItTime(int waitMillis);
	static void ResetDateTime(char* date, char* time);
	static String GetTimeStamp(bool dateOnly);
};
extern RTClockClass RTClock;

#endif

