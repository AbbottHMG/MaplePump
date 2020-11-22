// 
// 
// 

#include "TempCheck.h"
float  _inTemp;
float _outTemp;
float _lastInTemp;
float _lastOutTemp;
static EnumsClass::Temperature _inState;
static EnumsClass::Temperature _lastOutState;
static EnumsClass::Temperature _outState;
static EnumsClass::Action _lastPumpAction;
static OneWire _inOneWire(PINS_TEMP_IN_ONE_WIRE);
static OneWire _outOneWire(PINS_TEMP_OUT_ONE_WIRE);
static DallasTemperature _inSensors;
static DallasTemperature _outSensors;

void TempCheckClass::Init()
{	
	_inSensors = DallasTemperature(&_inOneWire);
	_outSensors = DallasTemperature(&_outOneWire);
	// Start up the library 
	_inSensors.begin();
	_outSensors.begin();
	_lastPumpAction = EnumsClass::Action::StartUp;
	_lastInTemp = GetTemp(INSIDETEMP);
	_lastOutTemp = GetTemp(OUTSIDETEMP);
	
	TempCheckClass::SetTempStates(INIT_TEMP);
}
void TempCheckClass::SetTempStates(bool init = false) {
	_inTemp = TempCheckClass::GetTempFloat(INSIDETEMP);
	_outTemp = TempCheckClass::GetTempFloat(OUTSIDETEMP);
	// Set inside temps
	if (_inTemp < INSIDE_LOWTEMP) {
		_inState = EnumsClass::Temperature::InCold;
	}
	else if (_inTemp > INSIDE_HIGHTEMP) {
		_inState = EnumsClass::Temperature::InHot;
	}
	else {
		_inState = EnumsClass::Temperature::InInRange;
	}
	if (init) {
		// Initial outside temps
		if (_outTemp < OUTSIDE_LOWTEMP) {
			_outState = EnumsClass::Temperature::OutCold;
		}
		else if (_outTemp > OUTSIDE_HIGHTEMP) {
			_outState = EnumsClass::Temperature::OutInRange;
		}
		else {
			_outState = EnumsClass::Temperature::OutInRange;
		}
	}
	else {
		if (_outState == EnumsClass::Temperature::OutInRange &&
			_inTemp < OUTSIDE_LOWTEMP)
			_outState == EnumsClass::Temperature::OutCold;
		if (_outState == EnumsClass::Temperature::OutCold &&
			_outTemp > OUTSIDE_HIGHTEMP)
			_outState = EnumsClass::Temperature::OutInRange;
	}
	// finally

	if (init) {
		_lastOutState = _outState;
		_lastInTemp = _inTemp;
		_lastOutTemp = _outTemp;
	}
	LogClass::InTempF(String(_inTemp, 1));
	LogClass::OutTempF(String(_outTemp, 1));

}

	EnumsClass::Temperature TempCheckClass::GetInState() {
		return _inState;
	}
	
	EnumsClass::Temperature TempCheckClass::GetLastOutState() {		
		return _lastOutState;
	}
		
	EnumsClass::Temperature TempCheckClass::GetOutState() {		
		return _outState;
	}

	float TempCheckClass::GetTempFloat(int sensorId) {
		float temp = GetTemp(sensorId);
		return temp;
	}
	String TempCheckClass::GetTempStr(int sensorId) {
		String tempStr = "00.0";
		float temp = GetTemp(sensorId);
		tempStr = String(temp, 1);
		return tempStr;
	}
	float TempCheckClass::GetTemp(int sensorId) {
		float tempF;
		if (sensorId = INSIDETEMP) {
			_inSensors.requestTemperatures(); // Send the command to get temperature
			tempF = _inSensors.getTempFByIndex(0); // Index 0 = we only have 1 temp sensor
		}
		else {
			_outSensors.requestTemperatures(); // Send the command to get temperature
			tempF = _outSensors.getTempFByIndex(0); // Index 0 = we only have 1 temp sensor
		}
		return tempF;
	}


TempCheckClass TempCheck;

