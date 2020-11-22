// 
// 
// 

#include "SDCard.h"
static bool _openedFailed = true;
// File prefix is date, which force single logfile per day
	void SDCardClass::WriteToSD(String string, String filePrefix, String fileSuffix, String folder = "") {
		if (_openedFailed) return;
		String fileName = filePrefix + fileSuffix;
		if (folder != "") {
			fileName = folder + "/" + fileName;
		}

		File sdFile = SD.open(fileName, FILE_WRITE);

		// if the file opened okay, write to it:
		if (sdFile) {
			 Serial.print("Writing to ");
			 Serial.println(fileName);
			sdFile.println(string);
			// close the file:
			sdFile.close();
			 Serial.println("done.");
		}
		else {
			// if the file didn't open, print an error:
			Serial.println("error opening " + fileName);
		}
	}

	String SDCardClass::ReadFromSD(String filePrefix, String fileSuffix, String folder = "") {
		if (_openedFailed) return "";
		String contents = "";
		String fileName = filePrefix + fileSuffix;
		if (folder != "") {
			fileName = folder + +"/" + fileName;
		}

		File myFile = SD.open(fileName);
		if (myFile) {
			// Serial.println(fileName);

			// read from the file until there's nothing else in it:
			while (myFile.available()) {
				contents += myFile.read();
			}
			// close the file:
			myFile.close();
		}
		else {
			// if the file didn't open, print an error:
			// Serial.println("error opening test.txt");
		}
		return contents;
	}
	void SDCardClass::Init() {
		{pinMode(PINS_SD_CARD_SLAVE, OUTPUT); // required for SD lib
		digitalWrite(PINS_SD_CARD_SLAVE, HIGH);
			if (!SD.begin(4)) {
				Serial.println("sd initialization failed!");

			}
			else {
				Serial.println("sd initialization done.");
				_openedFailed = false;
			}
		}
	}
	void SDCardClass::WriteLogFile(String logJson) { 
		if (_openedFailed) return;
		const String myExt = ".txt";
		const String myDir = "log";
		if (!SD.exists(myDir))SD.mkdir(myDir);
		WriteToSD(logJson, RTClockClass::GetTimeStamp(DATE_ONLY), myExt, myDir);
	}
	void SDCardClass::WriteTempFile(String logJson) {
		if (_openedFailed) return;
		const String myExt = ".txt";
		const String myDir = "temp";
		if (SD.exists(myDir) == false)SD.mkdir(myDir);
		WriteToSD(logJson, RTClockClass::GetTimeStamp(DATE_ONLY), myExt, myDir);
	}
	String SDCardClass::GetHtmlFile(String name) {
		const String myExt = ".htm";
		const String myDir = "html";
	}
	File SDCardClass::OpenFile(String myDir, String fileName) {
		if (myDir.length() == 0) myDir = "temp";
		if (SD.exists(myDir) == false) { SD.mkdir(myDir); }
		String fullFilePath = (myDir + "/" + fileName);
		File myFile = SD.open(fileName);
		return myFile;
	}

SDCardClass SDCard;

