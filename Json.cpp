// 
// 
// 

#include "Json.h"
	static StaticJsonDocument <ESTIMATED_JSON_SIZE> jsonDoc;
	// Json string creation
String JsonClass::BuildJsonDoc() {
	String logJson;
	jsonDoc.clear();

	jsonDoc["Date"] = LogClass::Date();
	jsonDoc["Action"] = LogClass::Action();
	jsonDoc["Active"] = LogClass::ActiveLines();
	jsonDoc["Broken"] = LogClass::BrokenLines();
	jsonDoc["FreeRam"] = LogClass::FreeRam();
	jsonDoc["InTmpF"] = LogClass::InTempF();
	jsonDoc["InTmpF"] = LogClass::OutTempF();
	jsonDoc["State"] = LogClass::State();
	

	jsonDoc["FlowRate"] = LogClass::FlowRate();
	jsonDoc["FlowLast"] = LogClass::FlowLast();
	jsonDoc["FlowTot"] = LogClass::FlowTot();
	jsonDoc["JsonLen"] = LogClass::JsonLen();
	jsonDoc["Vacuum"] = LogClass::VacuumPsi();	
	LogClass::JsonLen(String(jsonDoc.memoryUsage()));
	jsonDoc["JsonLen"] = LogClass::JsonLen();
	
	Serial.println();

	serializeJsonPretty(jsonDoc, logJson);
	
	Serial.print("Json - ");
	Serial.println(logJson);
	Serial.println();
	int count = 0;
	return logJson;
}

JsonClass Json;

