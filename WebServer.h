// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Ethernet.h>
#include <HashMap.h>
#include "Log.h"
#include "Logger.h"
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <SPI.h>
#include "SDCard.h"
#include "Statics.h"
typedef void (*function_pointer)();
class WebServerClass
{
	// Requests are of the form
	//   ?token&data1&data2,....

public:
	static HashMap<String, String> BuildCallParams(String callParams);
	static void CheckWebRequest();
	static String CreateHtmlPage();
  static void DownloadFromClient(String fileName);
	static void DownloadFileFromClient(String fileName, SDLib::File file);
	static void FileNotFound(String fileName);
	static void Init(void (*shutdownPointer)(), void (*restartPointer)(), bool isEthernetServer);
	static SDFile OpenSDFile(String fileName, int readWrite);
	static void PrintWifiStatus();
	static void RouteRequest(String readString);
	static void Send404(HashMap<String, String> callParams);
	static bool StoreNextParam(HashMap<String, String>* callHash, String* callParams);
	static void UpdateDateTime(String inDate, String inTime);
	static SDFile UploadToClient(String fileName);
};

extern WebServerClass WebServer;

#endif
