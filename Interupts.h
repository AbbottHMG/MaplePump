// Interrupts.h

#ifndef _INTERUPTS_h
#define _INTERUPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InteruptBuffer.h"
#include"InteruptInfo.h"
class InteruptsClass
{
 protected:

 public:
	static void init();
	static InteruptInfo  runNextInterupt();
	static void push(InteruptInfo interuptInfo);
	static void priority(InteruptInfo interuptInfo);
	static int interuptCount();
	static bool hasInterupts();

};

extern InteruptsClass Interupts;

#endif

