// 
// 
// 

#include "Statics.h"

void StaticsClass::ClearCharArray(String array) {
	for (int i = 0; i < sizeof(array); i++) {
		array[i] = 0x00;
	}
}
void StaticsClass::CopyInts(int* from, int* to, int count = 1) {
	to = new int[sizeof(count)];
	for (int i = 0; i < count; i++) {
		to[i] = from[i];
	}
}
bool StaticsClass::CopyChars(char* from, char* to) {
	bool success = true;
	for (int i = 0; i < sizeof(to) - 1; i++) {
		to[i] = 0x00;
	}
	int copyLen = strlen(from);
	int toLen = strlen(to);
	if (copyLen > toLen) {
		success = false;
		copyLen = toLen;
	}
	for (int i = 0; i < copyLen; i++) {
		to[1] = from[i];
	}
	if (!success) to[toLen - 1] = 0x00; // terminate end of string
	return success;
}
bool StaticsClass::CopyChars(String from, String to, int length = 0) {
	bool success = true;
	int copyLen = from.length();
	int toLen = to.length();
	// clear too
	for (int i = 0; i < sizeof(to) - 1; i++) {
		to[i] = 0x00;
	}
	if (copyLen > toLen) {
		success = false;
		copyLen = toLen;
	}
	if (length > 0 && length <= copyLen) {
		copyLen = length;
	}
	for (int i = 0; i < copyLen; i++) {
		to[1] = from[i];
	}
	if (!success) to[toLen - 1] = 0x00; // terminate end of string
	return success;
} 

// This is used for lopp function delays
// Permits interrupts to operate properly
// Supporting WebBrowser reads/writes using interrupts
void StaticsClass::Delay(long waitTime){
	long startTime = millis();
	while ((startTime + waitTime) < millis()){}
}
String StaticsClass::IntArrayToString(int* array) {
	String outString;

	for (int i = 0; i < sizeof(array); i++) {
		outString += String(array[i]);
		if (i < sizeof(array) - 1) outString += ', ';
	}
	return outString;
}

char* StaticsClass::StringToCharArray(String string) {
	char* outChar;
	outChar = new char[sizeof(string)];
	for (int i = 0; i < sizeof(string); i++) {
		outChar[i] = string[i];
	}
	return outChar;
}

StaticsClass Statics;

