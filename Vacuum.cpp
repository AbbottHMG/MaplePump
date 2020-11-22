// 
// 
// 

#include "DefinedValues.h"
#include "Vacuum.h"

	/* Reads pressure from the given pin.
	* Returns a value in Pascals
	* https://forum.arduino.cc/index.php?topic=401642.0
	*/
	static int _testLoopCount = 0;
	static bool _isTesting = false;
	static int _testLineState[9];

	void Init(){
		// do nothing
	}
	String VacuumClass::GetVacuumPsiStr() {
		char* s;
		dtostrf(GetVacuumPsi(), 4, 1, s);
		return String(s);
	}
	float VacuumClass::GetVacuumPsi() {
		int vacuum = analogRead(PINS_VACUUM_ANALOG);
		// params from spec sheet
		//int kPaInt = map(vacuum, 41, 986, 0, 256);
		float kPaFloat = ((vacuum / 1024.0) - 0.04) / 0.00369;
		float psiFloat = kPaFloat / 6.89475728;
		return psiFloat;
	}

	
	// line indicates which line is requesting the vacuum
	// 0 = full line test - default
	bool VacuumClass::IsVacuumLost() {
		const float _stdVacuumPsi = 5; // vacuum to compare to		
		return VacuumClass::GetVacuumPsi() < VACUUM_PUMP_BASE_PSI;
	}

	// creates random list if open lines

	bool VacuumClass::IsTestLostPressure(int line = 0){
		if(line == 0){
			if (_testLoopCount++ > TESTLOOPLIMIT){
				_testLoopCount = 0;
				//SetTestLineStates();
			}
			return true;
		}
		else{
			return _testLineState[line] == 1;
		}
	}
	/*void SetTestLineStates(){
		srandom(millis());
		for (int i = 1; i <= sizeof(_testLineState); i++){
			int randInt = rand();
			float randTest = 1 / randInt;
			if (randTest > .5){
				_testLineState[i] = 1;
			} else{
				_testLineState[i] = 0;
			}
		}
	}*/
VacuumClass Vacuum;

