// 
// 
// 

#include "DefinedValues.h"
#include "SapLine.h"

byte pinLED;
int _lineNumber = 0;
unsigned long _timeLineFailed = 0;
unsigned long _priorTimeFailed = 0;

bool _IsBreached = false;
bool _isOn = false;

void SapLineClass::Init(int lineNumber) {
	_lineNumber = lineNumber;
	ShutMeOff();
}

bool SapLineClass::IsOn() {
	return _isOn;
}
bool SapLineClass::IsOff() {
	return !_isOn;
}

bool SapLineClass::IsLineOk() {
	
	return !_IsBreached;
}

unsigned long SapLineClass::TimePriorFailed() {
	return _priorTimeFailed;
}

unsigned long SapLineClass::TimeLineFailed() {
	return _timeLineFailed;
}


void SapLineClass::ShutMeOff() {
	ValveRelaysClass::CloseValve(LINE_VALVES, _lineNumber);
	_isOn = false;
}

void SapLineClass::TurnMeOn() {
	ValveRelaysClass::OpenValve(LINE_VALVES, _lineNumber);
	_isOn = true;
}
SapLineClass SapLine;

