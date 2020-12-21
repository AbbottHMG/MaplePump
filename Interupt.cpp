// interrupts.cpp
// 
// 
#include "Interupt.h"
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

void InteruptClass::init() {
	Serial.print("enter Interrupt");
	InteruptBufferClass::init();
}

bool InteruptClass::push(InteruptorClass interuptor){
	InteruptBufferClass::push(interuptor);
}

int InteruptClass::interuptCount(){
		return InteruptBufferClass::size();	
}

bool InteruptClass::priority(InteruptorClass interuptor){
	InteruptBufferClass::pushhead(interuptor);
}

bool InteruptClass::hasInterupts(){
	int interruptCount = InteruptBufferClass::size();
	return (interruptCount > 0);
}

InteruptorClass InteruptClass::runNextInterupt()
{
	InteruptorClass interuptor  = InteruptBufferClass::peek();
	if(interuptor.canRunFunction()){
		interuptor.runInterupt();
		if(interuptor.canInteruptInfoBeDeleted()){
			InteruptBufferClass::pop();
		}
	}
	else 
	{
	// do nothimg
	}
}

void InteruptClass::startInterupts(){

}

void InteruptClass::stopInterupts(){

}
InteruptClass Interrupt;

