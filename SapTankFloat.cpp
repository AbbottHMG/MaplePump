// 
// 
// 

#include "SapTankFloat.h"
static bool _floatIsHigh = false;
static bool _tankFloatInterruptRaised = false;;
// THe tank float switch is attached between PINS_FLOAT_SWITCH and ground 
void SapTankFloatClass::Init()
{
	pinMode(PINS_FLOAT_SWITCH, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PINS_FLOAT_SWITCH), SapTankFloatClass::FloatStateChanged, CHANGE);
	SapTankPumpClass::Init();
}
void SapTankFloatClass::FloatStateChanged() {
	// Since we use INPUT_PULLUP LOW = float high (curcuit closed)
	noInterrupts(); //stop interrupts 
	_tankFloatInterruptRaised = true;
	SapTankFloatClass::ProcessStateChange();
	interrupts();//allow interrupts
}

void SapTankFloatClass::ProcessStateChange() {
	_floatIsHigh = digitalRead(PINS_FLOAT_SWITCH) == LOW;
}

bool SapTankFloatClass::HasStateChangePumpControl(bool isTempInRange) {
	if (_tankFloatInterruptRaised) {

	}
	return _tankFloatInterruptRaised;
}

bool SapTankFloatClass::IsFloatHigh() {
	_tankFloatInterruptRaised = false;
	return _floatIsHigh;
}
bool SapTankFloatClass::IsFloatLow() {
	_tankFloatInterruptRaised = false;
	return ! _floatIsHigh;   
}

SapTankFloatClass SapTankFloat;

