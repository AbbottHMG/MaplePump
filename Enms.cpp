#include "Enms.h"


String EnumsClass::EnumStr(EnumsClass::Action action){
	switch(action){
	case EnumsClass::FlowCheck:
		return "Flw";
		break;
	case EnumsClass::HeatOff:
		return "HOf";
		break;
	case EnumsClass::HeatOn:
		return "HOn";
		break;
	case EnumsClass::Initializing:
		return "Init";
		break;
	case EnumsClass::LineCheck:
		return "LI";
		break;
	case EnumsClass::NoAction:
		return "NO";
		break;
	case EnumsClass::ShutDown:
		return "SH";
		break;
	case EnumsClass::StartUp:
		return "ST";
		break;
	case EnumsClass::ToCold:
		return "TC";
		break;
	case EnumsClass::ToWarm:
		return "TW";
		break;
	case EnumsClass::VaccumCheck:
		return "VC";
		break;
	default:
		return "??";
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
		return "??";
		break;
	}
}
String EnumsClass::EnumStr(EnumsClass::State state){
	switch (state)
	{
	case EnumsClass::Cold: 
		return "Cld";
		break;
	case EnumsClass::NoFlow:
		return "NoF";
		break;
	case EnumsClass::Running:
		return "Rn";
		break;
	case EnumsClass::Starting:
		return "Strt";
		break;
	case EnumsClass::StartUp:
		return "Strt";
		break;
	case EnumsClass::Stopped:
		return "Stpd";
		break;
	case EnumsClass::Stopping:
		return "Stpng";
		break;
	case EnumsClass::VacuumClean:
		return "VClean";
		break;
	default:
		return "??";
		break;
	}
}

String EnumsClass::EnumStr(EnumsClass::Temperature temperature) {
	switch (temperature)
	{
	case EnumsClass::InCold:
		return "In cold";
		break;
	case EnumsClass::InHot:
		return "In Hot";
		break;
	case EnumsClass::InInRange:
		return "In Range";
		break;
	case EnumsClass::OutCold:
		return "Out Cold";
		break;
	case EnumsClass::OutInRange:
		return "Out Range";
		break;
	default:
		return "??";
		break;
	}
}

String EnumsClass::EnumStr(EnumsClass::Interrupt interrupts) {
	switch (interrupts)
	{
	case EnumsClass::CheckInTemp:
		return "CheckInTemp";
		break;
	case EnumsClass::CheckMinSensors:
		return "CheckMinSensors"; 
		break;
	case EnumsClass::CheckSapFloat:
		return "CheckSapFloat";
		break;
	case EnumsClass::CheckSapLines:
		return "CheckSapLines";
		break;
	case EnumsClass::Void:
		return "Void";
		break;
	}
}