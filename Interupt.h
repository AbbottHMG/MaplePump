// Interrupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enums.h"
#include "InteruptBuffer.h"

class InteruptClass
{
private:
public:
	static void init ();
	static bool push(InteruptorClass interuptor);
	static bool priority(InteruptorClass interuptor);
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
	static void startInterupts();
	static void stopInterupts();
};

extern InteruptClass Interupt;

#endif

