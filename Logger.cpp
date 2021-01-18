// 
// 
// 

#include "Logger.h"
static String lineString1;
static String lineString2;
void LoggerClass::Init() {
	lineString1.reserve(25);
	lineString2.reserve(25);
}

String LoggerClass::LogEntry() {
	int ram = FreeRam();
	String sRam = String(ram);
	LogClass::FreeRam(sRam);
	LoggerClass::DisplayLCDLines();
	String logJson = JsonClass::BuildJsonDoc();
	//Serial.println(logJson);
	SDCardClass::WriteLogFile(logJson); 
	return logJson;
}
 

// When ever we log we also update LCD display
String LoggerClass::DisplayLCDLines() {
		lineString1= LogClass::State() + "|";
		lineString1+= LogClass::OutTempF() + "|";
		lineString1+= LogClass::InTempF();
		LCDClass::PrintLn(lineString1, 0);
		Serial.println(lineString1);
		lineString2 = LogClass::ActiveLines() + "|";
		lineString2+= LogClass::BrokenLines() + "|";
		lineString2+= LogClass::VacuumPsi();
		LCDClass::PrintLn(lineString2, 1);
		Serial.println(lineString2);
	return lineString1 +"..." + lineString2;
}


LoggerClass Logger;

