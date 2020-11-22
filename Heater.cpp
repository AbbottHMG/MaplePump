// 
// 
// 

#include "Heater.h"

static volatile bool _heaterOn = false;

void HeaterClass::Init() {
	pinMode(PINS_HEATER, OUTPUT);
	//turn heater off
	digitalWrite(PINS_HEATER, LOW);
}

bool HeaterClass::IsHeaterOff() {
	return !_heaterOn;
}

bool HeaterClass::IsHeaterOn() {
	return _heaterOn;
}
void HeaterClass::SetHeater(bool setOn) {
	if (!setOn && _heaterOn) {
		HeaterClass::TurnHeaterOff();
			return;
	}if (setOn && !_heaterOn) {
		HeaterClass::TurnHeaterOn();
		return;
	}
	// all other cases ... do nothing: already on or off
}
void HeaterClass::TurnHeaterOff() {
	_heaterOn = false;
	//turn heater off
	digitalWrite(PINS_HEATER, LOW);
	Serial.println("Heater on");
}

void HeaterClass::TurnHeaterOn() {	
	//turn heater oon
	digitalWrite(PINS_HEATER, HIGH);
	_heaterOn = true;
	Serial.println("Heater on");
}