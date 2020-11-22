

#include "ValveRelays.h"

static int valvePins[2][9];

	void ValveRelaysClass::Init() {
		StaticsClass::CopyInts(ValvePinsAll, valvePins[0], RelayCount[0]);
		StaticsClass::CopyInts(ValveBypassPins, valvePins[1], RelayCount[1]);
	}

	void ValveRelaysClass::ValveRelaysClass::SetValvePinsToOutput(int valveSet) {
		for (int i = 1; i <= RelayCount[valveSet]; i++) {
			pinMode(valvePins[valveSet][i], OUTPUT);
		}
	}
	int* ValveRelaysClass::GetPins(int valveSet) {
		return valvePins[valveSet];
	}
	int ValveRelaysClass::ValveRelaysClass::TurnOnAllValves(int valveSet) {
		for (int i = 1; i == RelayCount[valveSet]; i++) {
			ValveRelaysClass::OpenValve(valveSet, i);
		}
		return RelayCount[valveSet];
	}
	int ValveRelaysClass::TurnOffAllValves(int valveSet) {
		for (int i = 1; i <= RelayCount[valveSet]; i++) {
			ValveRelaysClass::CloseValve(valveSet, valvePins[valveSet][i]);
		}
		return RelayCount[valveSet];
	}
	void ValveRelaysClass::CloseValve(int valveSet, int lineNumber) {
		digitalWrite(valvePins[valveSet][lineNumber], LOW);
		StaticsClass::Delay(VALVE_DELAY);
	}
	void ValveRelaysClass::OpenValve(int valveSet, int lineNumber) {
		digitalWrite(valvePins[valveSet][lineNumber], HIGH);
		StaticsClass::Delay(VALVE_DELAY);
	}

ValveRelaysClass ValveRelays;

