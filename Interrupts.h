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
#include <FIFO_CB.h>

class InterruptsClass
{

private:
public:
	static void CheckPins();
	static void Init();
	//static void AttachInterrupt(uint8_t intId, void (*callBack)(), int mode);
	//static void DetachInterrupt(uint8_t intId);
	//static void SetupInterrupts();
	static bool IsInterruptQueued();
	static int QueueSize();
	static void TimeCheckSensors();
	static void Restart();
	static void RunNextInterruptFunction();
	static void StartInterrupts();
	static void StopInterrupts();
	static void Shutdown();
};

extern InterruptsClass Interrupts;

#endif

