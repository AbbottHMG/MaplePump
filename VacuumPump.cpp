// 
// 
// 
#include "DefinedValues.h"
#include "FlowMeter.h"
#include "ValveRelays.h"
#include "VacuumPump.h"

	bool _turnedOn;
	unsigned long _timeLastOnOff;

	void VacuumPumpClass::Init() {
		pinMode(PINS_VACUUM_PUMP, OUTPUT);           // set pin to output
		_turnedOn = false;
		_timeLastOnOff = millis();
		VacuumPumpClass::TurnOff();
	}

	void VacuumPumpClass::CheckPumpFlow(){
		
		if (FlowMeterClass::FlowRate() == 0.0 && VacuumPumpClass::IsOn) {
			VacuumPumpClass::TurnOff();
		}
		if (FlowMeterClass::FlowRate() > 0.0 && !VacuumPumpClass::IsOn) {
			VacuumPumpClass::TurnOn();
		}
	}

	bool VacuumPumpClass::IsOff() {
		return ! _turnedOn;
	}

	bool VacuumPumpClass::IsOn() {
		return _turnedOn;
	}

	void VacuumPumpClass::TurnOn() {
		if (!_turnedOn) {
			StopBypass();
			StaticsClass::Delay(PUMP_ONOFF_DELAY);
			_timeLastOnOff = millis();
			// set pump relay pin high
			digitalWrite(PINS_VACUUM_PUMP, HIGH);
			CompleteBypass();
			_turnedOn = true;
			Serial.println("Vaccum Pump on");
		}
	}

	void VacuumPumpClass::TurnOff() {
		if (_turnedOn) {
			StartBypass();
			StaticsClass::Delay(PUMP_ONOFF_DELAY);
			_timeLastOnOff = millis();
			// set pump relay pin low
			digitalWrite(PINS_VACUUM_PUMP, LOW);
			OpenPumpValve();
			_turnedOn = false;
			Serial.println("Vaccum Pump off");
		}
	}

	// Pump Bypass valve handling
	// When turning pump off - start bypass then close vacuum valve
	void VacuumPumpClass::StartBypass(){
		ValveRelaysClass::OpenValve(BYPASS_VALVES, BYPASS_VALVE_INDEX);
	}
	void VacuumPumpClass::CompleteBypass(){
		ValveRelaysClass::CloseValve(BYPASS_VALVES, PUMP_VALVE_INDEX);
	}
	void VacuumPumpClass::StopBypass(){
		ValveRelaysClass::CloseValve(BYPASS_VALVES, BYPASS_VALVE_INDEX);
	}
	void VacuumPumpClass::OpenPumpValve(){
		ValveRelaysClass::OpenValve(BYPASS_VALVES, PUMP_VALVE_INDEX);
	}

VacuumPumpClass VacuumPump;

