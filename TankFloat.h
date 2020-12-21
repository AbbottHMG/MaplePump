// TamkFloat.h

#ifndef _TAMKFLOAT_h
#define _TAMKFLOAT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DefinedValues.h"
#include "SapTankPump.h"
class TankFloatClass
{
 protected:
	 static void FloatStateChanged();

 public:
	static void Init();
	static bool IsFloatHigh();
	static bool IsFloatLow();
	static void ProcessStateChange();
};

extern TankFloatClass TamkFloat;

#endif

