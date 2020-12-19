// Interuptor.h

#ifndef _INTERUPTOR_h
#define _INTERUPTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enms.h"
typedef void (*fPointer)();
class InteruptorClass
{
 protected:


 public:
	void init(void (*fPointer)(),
		long cycle,
		int repeats,
		EnumsClass::Interupt interupt);
	bool canRunFunction();
	bool canInteruptInfoBeDeleted();
	EnumsClass::Interupt Interupt();
	void runInterupt();
private:
	
	EnumsClass::Interupt _interupt;
	long _lastMillis;
	long _cycle;
	int _repeats ;
	int _repeatCount = 0;
	fPointer _fPointer;
};

extern InteruptorClass Interuptor;

#endif

