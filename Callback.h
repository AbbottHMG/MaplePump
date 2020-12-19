// Callback.h

#ifndef _CALLBACK_h
#define _CALLBACK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InteruptBuffer.h"
#include "Enms.h"
class CallbackClass
{
 protected:
	static EnumsClass::Interupt _thisInterrupt;
	 static long _millisLast;
	 static long _millisWait; // lenght of wait for last function call
	 static bool okToRun();
	 virtual void run(); 
 public:
	static void init(long millisWait);
};

extern CallbackClass Callback;

#endif

