// 
// 
// 

#include "TankFloat.h"
static bool _floatIsHigh = false;
// THe tank float switch is attached between PINS_FLOAT_SWITCH and ground 
void TankFloatClass::Init()
{
	pinMode(PINS_FLOAT_SWITCH, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PINS_FLOAT_SWITCH), TankFloatClass::FloatStateChanged, CHANGE);
}
void TankFloatClass::FloatStateChanged() {
	// Since we use INPUT_PULLUP LOW = float high (curcuit closed)
	cli();//stop interrupts 
	TankFloatInterruptRaised = true;
	TankFloatClass::ProcessStateChange();
	sei();//allow interrupts
}

void TankFloatClass::ProcessStateChange() {
	TankFloatInterruptRaised = false;
	_floatIsHigh = digitalRead(PINS_FLOAT_SWITCH) == LOW;
}
bool TankFloatClass::IsFloatHigh() {
	return _floatIsHigh;
}
bool TankFloatClass::IsFloatLow() {
	return ! _floatIsHigh;   
}

TankFloatClass TankFloat;

