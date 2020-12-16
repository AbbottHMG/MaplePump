// CallbackSensorCheck.h

#ifndef _CALLBACKSENSORCHECK_h
#define _CALLBACKSENSORCHECK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Callback.h"
class CallbackSensorCheckClass: CallbackClass
{
 protected:


 public:
	void init();
	bool run();
};

extern CallbackSensorCheckClass CallbackSensorCheck;

#endif

