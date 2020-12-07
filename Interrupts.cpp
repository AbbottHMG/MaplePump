// interrupts.cpp
// 
// 
#include "Interrupts.h"
#include "FIFO_AF.h"
/*
Interrupt notes
	There are three interrupts types used in the pump system:
		Timed – Every second. This is used by `the temperature and vacuum calculations
		routines, along with the vacuum test.
		Tank float - Whenever the status of the tank float changes: Full or empty, a change interrupt is raised.
		Flow meter - for each rotation of the flowmeter and interrupt is raised to increment the flow counter.
		
		The timed and senssor test Interrupts set flags that are tested in the sketch loop. The flowmeter interrupt just increments The counter.Flow calculations are performed anytime a log record is created.
		The priority order of handling the interrupts are:Tank float then timed interrupts. 
		The vacuum interrupt is handled in eight slices, one for each line. 
		Each line is tested through One iteration of the loop.
		The first iteration Tests the vacuum and closes all the lines if vacuum is lost.
		Each subsequent iteration tests the next line.

		Once this is operational, integration with the web server time slices will be done.
*/
/*
Timed Line interrupt approach:
When the loop occurs, we check to see which, if any, interrupt is to be flagged to be run in this iteration.
There are 2 options:
 !: Run a specific timed interrupt;
	a: Check Sensors (seys appropriate flags)
	b: Manage Heater
	c: Manage SapPump
	d: Manage vacuum pump
 2: Run a single “line” of the line check
	For the first rep (counter preset to 0), close the all the lines, set rep counter to 1, set timer to 2 seconds
	Calls close lines (2-8)s – using Statics::Delay (2) for 2 seconds,
	line1 force open
	return
Each rep:
		Open line – Delay(2)
		Check Vacuum – if ok, leave open, else  close, set line state
		Counter++
		return
*/
// Timed interupt clocks
static volatile long _lastTempMillis;
static volatile long _lastVaccumMillis;

static volatile long _lastTimer1;
static volatile int _infosCount = 0;
// static InterruptInfoClass interruptInfos[INTERRUPT_INFOS_SIZE];
static FIFO_AF fifoQueue;


void InterruptsClass::Init() {
	Serial.print("enter Interrupt");

int InterruptsClass::QueueSize() {
	return fifoQueue.size();
}

void InterruptsClass::TimeCheckSensors() {
	fifoQueue.push(InterruptsClass::CheckSensors);
}

bool InterruptsClass::IsInterruptQueued() {
	return fifoQueue.size() > 0;
}          

int QueueSize() {
	return fifoQueue.size();
}
void InterruptsClass::GetNextInterruptFunction() {
	int a = fifoQueue.size();
	if(fifoQueue.size() > 0) {
		fifoQueue.pop()();
	}
}
void InterruptsClass::CheckPins() { 
}
void InterruptsClass::Restart() {
	
}
void InterruptsClass::Shutdown() {
	
}

InterruptsClass Interrupts;

