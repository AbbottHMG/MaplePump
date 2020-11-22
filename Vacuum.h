// Vacuum.h

#ifndef _VACUUM_h
#define _VACUUM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class VacuumClass {
private:
	static bool IsTestLostPressure(int line);
public:
	/* Reads pressure from the given pin.
	* Returns a value in Pascals
	* https://forum.arduino.cc/index.php?topic=401642.0
	*/
	static void Init();
	static String GetVacuumPsiStr();
	static float GetVacuumPsi();
	static bool IsVacuumLost();
};

extern VacuumClass Vacuum;

#endif

