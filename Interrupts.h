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

class InterruptsClass
{
private:
public:
	static void CheckPins();
	static void Init();
	static bool IsInterruptQueued();
	static void TimeCheckSensors();
	static void Restart();
	static void RunNextInterruptFunction();
	static void StartInterrupts();
	static void StopInterrupts();
	static void Shutdown();
};

extern InterruptsClass Interrupts;

#endif

