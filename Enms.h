// Enms.h

#ifndef _ENMS_h
#define _ENMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EnumsClass
{
 public:
	  
	 enum SapLineState {
		 DONE,
		 CLOSE_ALL,	// On throughout close, until all are closed
		 OPENNING,	// Open line to test
		 CLOSING,	// Close leaking line
		 NEXT_LINE,	// Go to next line at next iterration
	 };

	 enum JsonType {
		 LOG_DATA,
		 TEMPERATUE_DATA,
		 VACUUM_DATA,
	 };
	 enum State {
		 Cold,
		 NoFlow,
		 Running,
		 Starting,
		 Stopped,
		 Stopping,
		 VacuumClean,
	 };
	 enum Action {
		FlowCheck,
		HeatInRange,
		HeatOff,
		HeatOn, 
		Initializing,
		LineCheck,
		NoAction,
		ShutDown,
		StartUp,
		ToCold,
		ToWarm,
		VaccumCheck,
	 };

	 enum Temperature {
		 InCold,
		 InHot,
		 InInRange,
		 OutCold,
		 OutInRange,
	 };

	 enum Interrupt{
		CheckInTemp,
		CheckMinSensors, // vacuum, outTemp
		CheckSapFloat,
		CheckSapLines,
		Void,
	 };

	 static String EnumStr(Action action);
	 static String EnumStr(JsonType jsonType);
	 static String EnumStr(State state);
	 static String EnumStr(Temperature temperature);
	 static String EnumStr(Interrupt interrupt);
};

extern EnumsClass Enms;

#endif

