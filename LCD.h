// LCD.h

#ifndef _LCD_h
#define _LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal_I2C.h>
class LCDClass
{
public:
	static void PrintLn(String message, int rowNo);
	static void Init();
};

extern LCDClass LCD;

#endif

