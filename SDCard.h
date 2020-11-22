// SDCard.h

#ifndef _SDCARD_h
#define _SDCARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SD.h> 
#include "RTClock.h"
#include "DefinedValues.h"

class SDCardClass
{
	/*
	The Ethernet / WiFi Shield comes with an SD card slot onboard. The shield fits on top of your Arduino. Because the Ethernet module uses pin 10, the CS pin for the SD card has been moved to pin 4. Make sure you use SD.begin(4) to use the SD card functionality.
	*/
private:
	static void WriteToSD(String string, String filePrefix, String fileSuffix, String folder = "");
	static String ReadFromSD(String filePrefix, String fileSuffix, String folder = "");
public:
	static void Init();
	static void WriteLogFile(String logJson);
	static void WriteTempFile(String logJson);
	static String GetHtmlFile(String name);
	static File OpenFile(String myDir, String fileName);
};

extern SDCardClass SDCard;

#endif

