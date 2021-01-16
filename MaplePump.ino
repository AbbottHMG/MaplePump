

// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       MaplePump.ino
    Created:	10/23/2019 3:33:20 PM
    Author:     ABBOTT-LAP\Abbott
*/

#include <OneWire.h>
#include "Heater.h"
#include "TankFloat.h"
#include "DefinedValues.h"
#include "Enums.h"
#include "FlowMeter.h"
#include "LCD.h"
#include "Logger.h"
#include "Log.h"
#include "RTClock.h"
#include "SapTankPump.h"
#include "SapLine.h"
#include "SapLines.h"
#include "SDCard.h"
#include "Statics.h"
#include "Task.h"
#include "TaskManager.h"
#include "TemperatureChecks.h"
#include "USBTester.h"
#include "Vacuum.h"
#include "VacuumPump.h"
#include "ValveRelays.h"
#include "WebServer.h"
#include <CircularBuffer.h>
static  CircularBuffer<TaskClass*, InterruptBufferSize> CBuffer;
static TaskClass Tasks[InterruptBufferSize];
SapLinesClass *sapLines = new SapLinesClass();

// Using Statics::Delay en lieu of Delay does not inhibit interrupts
static bool _setUpComplete = false;
void setup()
{
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
		TankFloatClass::Init(); // Controls SapTankPump
		//TempCheckClass::Init();
		VacuumPumpClass::Init();
		//SapTankPumpClass::Init();
		ValveRelaysClass::Init();
		sapLines->Init();
		SapLinesClass::TurnOnAllLines();
		Serial.println("Call Interrupt");
		//initializeState();
		Serial.print("Startup End Free RAM: ");
		Serial.println(FreeRam());

		Serial.println("Startup End");
		LoggerClass::LogEntry();
		_setUpComplete = true;
		//WebServerClass::Init(InterruptsClass::Shutdown, InterruptsClass::Restart, WEB_SERVER_ETHERNET);
	}
}
bool noMoreTasks;

void loop()
{
	//Just keep trying
	Serial.print("Trying - ");
	Serial.println(millis());
	noMoreTasks = TaskManagerClass::runNextTask();
	delay(5000);
	if (noMoreTasks) {
		Serial.print("No more Tasks");
	}
	else {
		TaskManagerClass::listBuffer();
	}
	
}
void LCD_DisplayTime() {

	String time = RTClockClass::GetTimeStamp(DATE_ONLY);
	LCDClass::PrintLn(time, 1);
	time = RTClockClass::GetTimeStamp(DATE_TIME);
	LCDClass::PrintLn(time, 2);
}