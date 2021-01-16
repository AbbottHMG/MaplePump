// TamkFloat.h

#ifndef _TAMKFLOAT_h
#define _TAMKFLOAT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SapTankPump.h"
#include "DefinedValues.h"
#include "SapTankPump.h"
class TankFloatClass
{
 protected:
	static void FloatStateChanged();
	static void ProcessStateChange();

 public:
	static void Init();
	static bool HasStateChangePumpControl(bool isTempInRange);
	static bool IsFloatHigh();
	static bool IsFloatLow();
};

extern TankFloatClass TamkFloat;

#endif

