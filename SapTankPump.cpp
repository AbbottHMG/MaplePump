// 
// 
// 

#include "SapTankPump.h"

static unsigned long timeLastOnOff;
static bool _turnedOn = false;
	void SapTankPumpClass::Init() {
		pinMode(PINS_SAP_TANK_PUMP, OUTPUT);
		//set pump off
		digitalWrite(PINS_SAP_TANK_PUMP, LOW);
		_turnedOn = false;
		timeLastOnOff = millis();
	}
	bool SapTankPumpClass::IsTankPumpOff() {
		return !_turnedOn;
	}
	bool SapTankPumpClass::IsTankPumpOn() {
		return _turnedOn;
	}
	void SapTankPumpClass::TurnTankPumpOn() {
		if (!_turnedOn) {
			StaticsClass::Delay(PUMP_ONOFF_DELAY);
			timeLastOnOff = millis();
			// set pump relay pin high
			digitalWrite(PINS_SAP_TANK_PUMP, HIGH);
			LogClass::SapPump(SAP_PUMP_ON);
			LoggerClass::LogEntry();
			_turnedOn = true;
			Serial.println(" Sap Pump on");
		}
	}
	void SapTankPumpClass::TurnTankPumpOff() {
		if (_turnedOn) {
			StaticsClass::Delay(PUMP_ONOFF_DELAY);
			timeLastOnOff = millis();
			// set pump relay pin low
			digitalWrite(PINS_SAP_TANK_PUMP, LOW);
			LogClass::SapPump(SAP_PUMP_OFF);
			LoggerClass::LogEntry();
			_turnedOn = false;
			Serial.println("Sap Pump off");
		}
	}

SapTankPumpClass SapTankPump;

