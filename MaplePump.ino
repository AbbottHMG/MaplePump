#include <OneWire.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       MaplePump.ino
    Created:	10/23/2019 3:33:20 PM
    Author:     ABBOTT-LAP\Abbott
*/

#include "Heater.h"
#include "TankFloat.h"
#include "DefinedValues.h"
#include "Enms.h"
#include "FIFO_AF.h"
#include "FlowMeter.h"
#include "Interrupts.h"
#include "LCD.h"
#include "Logger.h"
#include "Log.h"
#include "RTClock.h"
#include "SapTankPump.h"
#include "SapLine.h"
#include "SapLines.h"
#include "SDCard.h"
#include "Statics.h"
#include "USBTester.h"
#include "Vacuum.h"
#include "VacuumPump.h"
#include "ValveRelays.h"
#include "WebServer.h"
SapLinesClass *sapLines = new SapLinesClass();
// Using Statics::Delay en lieu of Delay does not inhibit interrupts
static bool _setUpComplete = false;
void setup()
{
	int testCount = 0;
	 Serial.begin(115200);
	 while (!Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
// Do all the initializtion here
	 LocalSetup();
}
 
void LocalSetup() {
	if (!_setUpComplete) {
		Serial.print(F("Startup Free RAM: "));
		int ram = FreeRam();
		String sRam = String(ram);
		Serial.println(ram);
		RTClockClass::Init();
		String name = EnumsClass::EnumStr(EnumsClass::State::Stopped);
		LogClass::State(name); 
		name = EnumsClass::EnumStr(EnumsClass::Action::Initializing);
		FlowMeterClass::Init();
		LogClass::Action(name);
		LoggerClass::Init();
		LCDClass::Init();
		SDCardClass::Init();
		TankFloatClass::Init();
		//TempCheckClass::Init();
		VacuumPumpClass::Init();
		SapTankPumpClass::Init();
		TankFloatClass::Init();
		ValveRelaysClass::Init();
		sapLines->Init();
		SapLinesClass::TurnOnAllLines();
		Serial.println("Call Interrupt");
		InterruptsClass::Init();
		//initializeState();
		Serial.print("Startup End Free RAM: ");
		Serial.println(FreeRam());
		Serial.println("Startup End");
		LoggerClass::LogEntry();
		_setUpComplete = true;
		//WebServerClass::Init(InterruptsClass::Shutdown, InterruptsClass::Restart, WEB_SERVER_ETHERNET);
	}
}
int NextCounter = 0;

void loop()
{

	int size = InterruptsClass::QueueSize();
	String time = RTClockClass::GetTimeStamp(DATE_TIME) + " :";
		Serial.println(time + size);
	if (CheckSensors) {
		//InterruptsClass::CheckSensors();
		Serial.println(time + " CheckSensors");
		CheckSensors = false;
	}
	size = InterruptsClass::QueueSize();
	Serial.println(size + "FifoSize");
	if(size > 0){
		InterruptsClass::RunNextInterruptFunction();
	}
	else{
		Serial.println(time + "Fifo Empty");
		//// runs for 1 web page cycle
		//WebServerClass::CheckWebRequest();
		//// when completed, we just continue
	}

	StaticsClass::Delay(10000);
}
void LCD_DisplayTime() {

	String time = RTClockClass::GetTimeStamp(DATE_ONLY);
	LCDClass::PrintLn(time, 1);
	time = RTClockClass::GetTimeStamp(DATE_TIME);
	LCDClass::PrintLn(time, 2);
}