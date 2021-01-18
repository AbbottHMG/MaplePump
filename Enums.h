// Enms.h

#ifndef _ENUMS_h
#define _ENUMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EnumsClass
{
 public:
	  
	 enum Action {
		CheckFlow,
		Initializing,
		LineCheck,
		NoAction,
		OutColdStop,
		OutWarmStart,
		ShutDown,
		StartUp,
		TurnHeatOff,
		TurnHeatOn, 
		VaccumCheck,
	 };

	 enum Interrupt{
		CheckInTemp,
		CheckMinSensors, // vacuum, outTemp
		CheckSecSensors, // float, in temp
		CheckSapFloat,
		CheckSapLines,
		InitializeVacuumTest,
		ShutOnOffSystem,
		VacuumTestAllLines,
		Unkown,
	 };

	 enum JsonType {
		 LOG_DATA,
		 TEMPERATUE_DATA,
		 VACUUM_DATA,
	 };
	 enum SapLineState {
		 DONE,
		 CLOSE_ALL_FOR_TEST,	// On throughout close, until all are closed
		 OPEN_A_LINE,	// Open line to test
		 CLOSE_A_LINE,	// Close leaking line
		 NEXT_LINE,	// Go to next line at next iterration
	 };

	 enum State {
		 NoFlow,
		 OutIsCold,
		 OutIsWarm,
		 Running,
		 Starting,
		 Stopped,
		 Stopping,
		 VacuumClean,
	 };

	 enum Temperature {
		 InCold,
		 InInRange,
		 OutCold,
		 OutInRange,
	 };

	 static String EnumStr(Action action);
	 static String EnumStr(JsonType jsonType);
	 static String EnumStr(State state);
	 static String EnumStr(Temperature temperature);
	 static String EnumStr(Interrupt interrupt);
};

extern EnumsClass Enums;

#endif

