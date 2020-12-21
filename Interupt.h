// Interrupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
<<<<<<< HEAD
#include "Enums.h"
=======
#include "DefinedValues.h"
#include "Enms.h"
>>>>>>> 6358d16... Bunch of changes
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
<<<<<<< HEAD
	static void startInterupts();
	static void stopInterupts();
=======
>>>>>>> 6358d16... Bunch of changes
};

extern InteruptClass Interupt;

#endif

