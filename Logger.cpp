// 
// 
// 

#include "Logger.h"
static String lineString;
void LoggerClass::Init() {
	lineString.reserve(25);
}
String LoggerClass::LogEntry() {
	int ram = FreeRam();
	String sRam = String(ram);
	LogClass::FreeRam(sRam);
	DisplayLines();
	String logJson = JsonClass::BuildJsonDoc();
	//Serial.println(logJson);
	SDCardClass::WriteLogFile(logJson); 
	return logJson;
}
 
String LoggerClass::DisplayLines() {
		lineString= LogClass::State() + "|";
		lineString+= LogClass::OutTempF() + "|";
		lineString+= LogClass::InTempF();
		LCDClass::PrintLn(lineString, 0);
		Serial.println(lineString);
		lineString = LogClass::ActiveLines() + "|";
		lineString+= LogClass::BrokenLines() + "|";
		lineString+= LogClass::VacuumPsi();
		LCDClass::PrintLn(lineString, 1);
		Serial.println(lineString);
	return lineString;
}


LoggerClass Logger;

