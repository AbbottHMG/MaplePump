// USBTester.h

#ifndef _USBTESTER_h
#define _USBTESTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class USBTesterClass
{
 public:
	 static bool IsUSBPowered();
};

extern USBTesterClass USBTester;

#endif

