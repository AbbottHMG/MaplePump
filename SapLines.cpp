// 
// 
// 


#include "SapLines.h"

static int* linesToUse;
static SapLineClass* _myLines[10];
static int* pins;
static int _lineCount;
static volatile int _activeLine;
static volatile enum EnumsClass::SapLineState _currentTestState;

/*
Line Checks:
Note: we do not use arduino delay but our Statics::Delay(waittime)
 Once there is a timed interrupt for Line Checks
 The CheckAllLines function is called.
 If there is vacuum loss, a turn-off all lines
 flag is set and the line-turn-off and line-test counters are set to 0
 and the function returns to loop.
 Each time the function is called, each line is turned off
 and when they are all turned off the line-tests start.
 There is a ?? second delay between each turn-off and test. 
 FOr the test, the line is turned-on and vacuum tested. If ng, it's turned off.
 Once all the line tests are done, the line-test log entry
 is written and the timed-interrupt flag is reset.
 The whole process should take less than a minute.
*/

// when a line is checked, if its ok, we chage the period to  .5sec
bool SapLinesClass::CheckALine(TaskClass* task) {
	_myLines[task->useCount()]->TurnMeOn();
	// Wait for line valve relay delay
	StaticsClass::Delay(Millis_5Sec);
	// for testing
#if DEBUG
	if (task->useCount() % 2 == 0) {
		_myLines[task->useCount()]->ShutMeOff();
	}
#else
	if (!VacuumClass::IsVacuumLost()) {
		_myLines[task->useCount()]->ShutMeOff();
	}
#endif
	if (task->useCount() == 0) {
		SetLogLineStates();
	}
}
void SapLinesClass::Init() {
	pins = ValveRelaysClass::GetPins(LINE_VALVES);
	_lineCount = sizeof(ValveRelaysClass::GetPins(LINE_VALVES) - 1);
	for (int i = 1; i <= _lineCount; i++) {
		_myLines[i]->Init(i);
	}
	String logString = GetActiveLines();
	LogClass::ActiveLines(logString);
	logString = GetBrokenLines();
	LogClass::BrokenLines(logString);
}
void SapLinesClass::SetLogLineStates() {
	LogClass::ActiveLines(SapLinesClass::GetActiveLines());
	LogClass::BrokenLines(SapLinesClass::GetBrokenLines());
	LogClass::VacuumPsi(VacuumClass::GetVacuumPsiStr());
}
String SapLinesClass::GetBrokenLines() {
	String lineList = {};
	for (int i = 0; i < _lineCount; i++) {
		if (_myLines[i]->IsOff()) {
			lineList = lineList + i + ',';
		}
	}
	return lineList;
}
String SapLinesClass::GetActiveLines() {
	String lineList = {};
	for (int i = 0; i < _lineCount; i++) {
		if (_myLines[i]->IsOn()) {
			lineList = lineList + i + ',';
		}
	}	
	return lineList;
}
int SapLinesClass::GetActiveLineCount() {
	int returnCount = 0;
	for (int i = 1; i <= _lineCount; i++) {
		if(_myLines[i]->IsOn()) returnCount++;
	}
	return returnCount;
}
void SapLinesClass::TurnOffAllLines() {
	for (int i = 1; i <= _lineCount; i++) {
		_myLines[i]->ShutMeOff();
	}
}
void SapLinesClass::TurnOnAllLines() {
	for (int i = 1; i <= _lineCount; i++) {
		_myLines[i]->TurnMeOn();
	}
}

SapLinesClass SapLines;

