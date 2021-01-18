#include "Enums.h"


String EnumsClass::EnumStr(EnumsClass::Action action){
	switch(action){
	case EnumsClass::CheckFlow:
		return "Flw";
		break;
	case EnumsClass::Initializing:
		return "Init";
		break;
	case EnumsClass::LineCheck:
		return "LI";
		break;
	case EnumsClass::NoAction:
		return "N/A";
		break;
	case EnumsClass::OutColdStop:
		return "OCS";
		break;
	case EnumsClass::OutWarmStart:
		return "OWS";
		break;
	case EnumsClass::ShutDown:
		return "SH";
		break;
	case EnumsClass::StartUp:
		return "ST";
		break;
	case EnumsClass::TurnHeatOff:
		return "TH+";
		break;
	case EnumsClass::TurnHeatOn:
		return "TH-";
		break;
	case EnumsClass::VaccumCheck:
		return "VC";
		break;
	default:
		return "Invalid Action";
		break;
	}
}
String EnumsClass::EnumStr(EnumsClass::JsonType jsonType){
	switch(jsonType){
	case EnumsClass::LOG_DATA:
		return "LG";
		break;
	case EnumsClass::TEMPERATUE_DATA:
		return "TP";
		break;
	case EnumsClass::VACUUM_DATA:
		return "VC";
		break;
	default:
		return "Invalid Json Type";
		break;
	}
}
String EnumsClass::EnumStr(EnumsClass::State state){
	switch (state)
	{
	case EnumsClass::NoFlow:
		return "NF";
		break;
	case EnumsClass::OutIsCold:
		return "OC";
		break;
	case EnumsClass::OutIsWarm:
		return "OW";
		break;
	case EnumsClass::Running:
		return "RN";
		break;
	case EnumsClass::Starting:
		return "STRG";
		break;
	case EnumsClass::Stopped:
		return "STPD";
		break;
	case EnumsClass::Stopping:
		return "STPG";
		break;
	case EnumsClass::VacuumClean:
		return "VC";
		break;
	default:
		return "Invalid State";
		break;
	}
}

String EnumsClass::EnumStr(EnumsClass::Temperature temperature) {
	switch (temperature)
	{
	case EnumsClass::InCold:
		return "ITC";
		break;
	case EnumsClass::InInRange:
		return "ITR";
		break;
	case EnumsClass::OutCold:
		return "OTC";
		break;
	case EnumsClass::OutInRange:
		return "OTR";
		break;
	default:
		return "Invalid Temp";
		break;
	}
}

String EnumsClass::EnumStr(EnumsClass::Interrupt interrupt) {
	switch (interrupt)
	{
	case EnumsClass::CheckInTemp:
		return "CheckInTemp";
		break;
	case EnumsClass::CheckMinSensors:
		return "CheckMinSensors"; 
		break;
	case EnumsClass::CheckSecSensors:
		return "CheckSecSensors";
		break;
	case EnumsClass::CheckSapFloat:
		return "CheckSapFloat";
		break;
	case EnumsClass::CheckSapLines:
		return "CheckSapLines";
		break;
	case EnumsClass::InitializeVacuumTest:
		return "InitializeVacuumTest";
		break;
	case EnumsClass::ShutOnOffSystem:
		return "ShutOnOffSystem";
		break;
	case EnumsClass::VacuumTestAllLines:
		return "VacuumTestAllLines";
		break;
	case EnumsClass::Unkown:
		return "Unkown";
		break;
	default:
		return "Invalid Interrupt";
		break;
	}
}