// Interrupts.h

#ifndef _INTERRUPTS_h
#define _INTERRUPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DefinedValues.h"
#include "Enms.h"
#include "InteruptBuffer.h"
#include "Interuptor.h"

class InterruptsClass
{
private:
public:
	static void push(InteruptorClass interuptor);
	static void priority(InteruptorClass interuptor);
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt()
};

extern InterruptsClass Interrupts;

#endif

