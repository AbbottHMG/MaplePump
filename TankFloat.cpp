// 
// 
// 

#include "TankFloat.h"
static bool _floatIsHigh = false;
static bool _tankFloatInterruptRaised = false;;
// THe tank float switch is attached between PINS_FLOAT_SWITCH and ground 
void TankFloatClass::Init()
{
	pinMode(PINS_FLOAT_SWITCH, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PINS_FLOAT_SWITCH), TankFloatClass::FloatStateChanged, CHANGE);
	SapTankPumpClass::Init();
}
void TankFloatClass::FloatStateChanged() {
	// Since we use INPUT_PULLUP LOW = float high (curcuit closed)
	cli();//stop interrupts 
	_tankFloatInterruptRaised = true;
	TankFloatClass::ProcessStateChange();
	sei();//allow interrupts
}

void TankFloatClass::ProcessStateChange() {
	_floatIsHigh = digitalRead(PINS_FLOAT_SWITCH) == LOW;
}

bool TankFloatClass::HasStateChangePumpControl(bool isTempInRange) {
	if (_tankFloatInterruptRaised) {

	}
	return _tankFloatInterruptRaised;
}

bool TankFloatClass::IsFloatHigh() {
	_tankFloatInterruptRaised = false;
	return _floatIsHigh;
}
bool TankFloatClass::IsFloatLow() {
	_tankFloatInterruptRaised = false;
	return ! _floatIsHigh;   
}

TankFloatClass TankFloat;

