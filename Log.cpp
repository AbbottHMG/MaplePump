#include "log.h"

  static String _action;
  static String _activeLines;
  static String _brokenLines;
  static String _dateTime;
  static String _fileName;
  static String _flowLast;
  static String _flowRate;
  static String _flowTot;
  static String _freeRam;
  static String _inTempF;
  static String _jsonLen;
    //todo Allocate 256b and allow value to be written
  static String _sapPump;
  static String _state;
  static String _outTempF;
  static String _vacuumPsi;
  static String _webAction;
  static String _webMessage;
  static String _webRequest; 

void LogClass::Init() {
	_action.reserve(11);
	_activeLines.reserve(9);
	_brokenLines.reserve(9);
	_dateTime.reserve(16);
	_fileName.reserve(64);
	_flowLast.reserve(6);
	_flowRate.reserve(6);
	_flowTot.reserve(7);
	_freeRam.reserve(6);
	_inTempF.reserve(5);
	_jsonLen.reserve(6);
	_outTempF.reserve(5);
	_sapPump.reserve(4);
	_state.reserve(11);
	_vacuumPsi.reserve(5);
	_webAction.reserve(11);
	_webMessage.reserve(81);
	_webRequest.reserve(11);
	_action="vacCheck";
	_activeLines="1234";
	_brokenLines="5678";
	_dateTime="2021-01-20-120000";
	_fileName="20210120";
	_flowLast="2.0";
	_flowRate="3.0";
	_flowTot="56.0";
	_freeRam="12345";
	_inTempF="37.0";
	_jsonLen = "2000";
	_outTempF="34.0";
	_sapPump = "Off";
	_state = "Off";
	_vacuumPsi="30.0";
	_webAction="Upload";
	_webMessage="ask me something";
	_webRequest="Get";
}
  
String LogClass::Action(String value){
	if(value.length() != 0)
		_action = value;
	String test = _action;
	// Serial.println("Act-" + _action);
	return _action;
}
String LogClass::ActiveLines(String value){
	if (value.length() != 0)
		_activeLines = value;
	// Serial.println("ALns-" + _activeLines);
	return _activeLines;
}
String LogClass::BrokenLines(String value){
	if(value.length() != 0)
		_brokenLines = value;
	// Serial.println("BLns-" + _brokenLines);
	return _brokenLines;
}
String LogClass::Date(){ 
  _dateTime = RTClockClass::GetTimeStamp(DATE_TIME);
  // Serial.println("Date-" + _dateTime);
  return _dateTime;
}
String LogClass::FileName(String value){
	if(value.length() != 0)
		_fileName = value;
	// Serial.println("FNm-" + _fileName);
	return _fileName;
}
String LogClass::FlowLast(String value){
	if(value.length() != 0)
		_flowLast = value;
	// Serial.println("FLst-" + _flowLast);
	return _flowLast;
}
String LogClass::FlowRate(String value){
	if(value.length() != 0)
		_flowRate = value;
	// Serial.println("FRte-" + _flowRate);
	return _flowRate;
}
String LogClass::FlowTot(String value){
	if(value.length() != 0)
		_flowTot = value;
	// Serial.println("FTot-" + _flowTot);
	return _flowTot;
}
String LogClass::FreeRam(String value){
	if(value.length() != 0)
		_freeRam = value;
	// Serial.println("FRam-" + _freeRam);
	return _freeRam;
}
String LogClass::InTempF(String value){
	if(value.length() != 0)
		_inTempF = value;
	// Serial.println("ITmp-" + _inTempF);
	return _inTempF;
}
String LogClass::JsonLen(String value){
	if(value.length() != 0)
		_jsonLen = value;
	// Serial.println("JsnL-" + _jsonLen);
	return _jsonLen;
}
String LogClass::OutTempF(String value){
	if(value.length() != 0)
		_outTempF = value;
	// Serial.println("OTmp-" + _outTempF);
	return _outTempF;
}	
String LogClass::SapPump(String value){
	if(value.length() != 0)
		_sapPump = value;	
	// Serial.println("SPmp-" + _stateamPump);
	return _sapPump;
}
String LogClass::State(String value) {
	if (value.length() != 0)
		_state = value;
	// Serial.println("Ste-" + _state);
	return _state;
}
String LogClass::VacuumPsi(String value){
	if(value.length() != 0)
		_vacuumPsi = value;
	// Serial.println("Vac-" + _vacuumPsi);
	return _vacuumPsi;
}
String LogClass::WebAction(String value){
	if(value.length() != 0)
		_webAction = value;
	// Serial.println("WAct-" + _webAction);
	return _webAction;
}
String LogClass::WebMessage(String value){
	if(value.length() != 0)
		_webMessage = value;
	// Serial.println("WMsg-" + _webMessage);
	return _webMessage;
}
String LogClass::WebRequest(String value){
	if(value.length() != 0)
		_webRequest = value;
	// Serial.println("WReq-" + _webRequest);
	return _webRequest;
}
