// 
// 
// 

#include "Log.h"
#include "DefinedValues.h"
#include "WebServer.h"

EthernetServer etherServer(80);
WiFiServer wifiServer(80);

static bool serverTypeIsEthernet;
static function_pointer _restartPointer;
static function_pointer _shutdownPointer;
static bool _noHardware;
static String _htmlContent; // This is read from SD card
static EthernetClient _etherClient;
static WiFiClient _wifiClient;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 10, 177);
IPAddress gateway(192, 168, 10, 1);
IPAddress dns(192, 168, 10, 1);

String WebServerClass::CreateHtmlPage() {
	String content;
	// Get the prototype html page
	if (_htmlContent.length() == 0) {
		_htmlContent = SDCardClass::GetHtmlFile(HTML_PAGE_NAME);
	}
	content = _htmlContent;
	content.replace("@ActiveLines", LogClass::ActiveLines());
	content.replace("@BrokenLines", LogClass::BrokenLines());
	content.replace("@FlowRate", LogClass::FlowRate());
	content.replace("@FlowTot", LogClass::FlowTot());
	content.replace("@JsonLenAct", (String(LogClass::JsonLen())));
	content.replace("@State", LogClass::State());
	content.replace("@Message", LogClass::WebMessage());
	content.replace("@TempF", LogClass::OutTempF());
	content.replace("@TimeDate", LogClass::Date());
	content.replace("@VacuumPsi", LogClass::VacuumPsi());
	content.replace("@WebAction", LogClass::WebAction());
	return content;
}
void WebServerClass::UpdateDateTime(String inDate, String inTime) {
	char* date = StaticsClass::StringToCharArray(inDate);  // might have single dig day
	char* time = StaticsClass::StringToCharArray(inTime);
	RTClockClass::ResetDateTime(date, time);
}
HashMap<String, String> WebServerClass::BuildCallParams(String callParams) {
	// Params format
	//	?action=action&param1=value1&param2=value2
	HashMap<String, String> callHash;
	String workParams = callParams;
	bool moreParams = true;
	do {
		moreParams = StoreNextParam(&callHash, &workParams);
	} while (moreParams);
	return callHash;
}
bool WebServerClass::StoreNextParam(HashMap<String, String>* callHash, String* callParams) {
	// parse call params backwards, as we extract eact we remove it
	bool returnOk = true;
	String value = "0123456789";
	String key = "0123456789";
	callParams[0] = "&"; // make all key starts the same (? -> &)
	int keyIndex;
	int valIndex = callParams->lastIndexOf('=');
	if (valIndex > -1) {
		int valPtr = valIndex++;
		value = callParams->substring(valPtr); //gets last value += 
		if (value.length() > 0) {
			callParams->remove(valIndex);
			keyIndex = callParams->lastIndexOf('&');
			if (keyIndex > -1) {
				int keyPtr = keyIndex++;
				key = callParams->substring(keyPtr); //gets last key += 
				callParams->remove(keyIndex);
			}
		}
		if (keyIndex == -1 || valIndex == -1) {
			returnOk = false;
		}
		else {
			callHash->put(key, value);
		}
	}
	return returnOk;
}
void WebServerClass::DownloadFromClient(String fileName) {
	// if there are incoming bytes available
	// from the server, read them and print them: 
	LogClass::FileName(fileName);
	SDFile file = WebServerClass::OpenSDFile(fileName, O_READ);
	if (serverTypeIsEthernet) {
		do {
			char c = _etherClient.read();
			file.print(c);
		} while (_etherClient.available());

		// if the server's disconnected, stop the client:
		if (!_etherClient.connected()) {
			// Serial.println();
			// Serial.println("disconnecting Ethernet.");
			_etherClient.stop();
			file.close();
			// Serial.println("Finished writing to file");
		}
	}
	else {
		do {
			char c = _wifiClient.read();
			file.print(c);
		} while (_wifiClient.available());

		// if the server's disconnected, stop the client:
		if (!_wifiClient.connected()) {
			// Serial.println();
			// Serial.println("disconnecting Wifi.");
			_wifiClient.stop();
			file.close();
			// Serial.println("Finished writing to file");
		}
	}
 	LogClass::WebMessage("Download File" + fileName);
	LoggerClass::LogEntry();
}
void WebServerClass::PrintWifiStatus() {
	// print the SSID of the network you're attached to:
	// Serial.print("SSID: ");
	// Serial.println(WiFi.SSID());

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	// Serial.print("IP Address: ");
	// Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	// Serial.print("signal strength (RSSI):");
	// Serial.print(rssi);
	// Serial.println(" dBm");
}
void WebServerClass::Init(void (*shutdownPointer)(), void (*restartPointer)(), bool isEthernetServer = true) {
	etherServer = EthernetServer(WEB_SERVER_PORT);
	wifiServer = WiFiServer(WEB_SERVER_PORT);
	_restartPointer = restartPointer;
	_shutdownPointer = _shutdownPointer;
	LogClass::WebAction(WEB_ACTION_NONE);
	// Wifi Setup params
	char ssid[] = "BarnRoom";      // your network SSID (name)
	//char pass[] = "Ryan1Dana1";   // your network password
	//int keyIndex = 0;                 // your network key Index number (needed only for WEP)
	int status = WL_IDLE_STATUS;
	// Start the server
	serverTypeIsEthernet = isEthernetServer;
	if (serverTypeIsEthernet) {
		Serial.println("Ethernet WebServer Class");
		// start the Ethernet connection and the server:
		Ethernet.begin(mac, ip, dns, gateway);

		// Check for Ethernet hardware present
		if (Ethernet.hardwareStatus() == EthernetNoHardware) {
			Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
			_noHardware = true;
		}
		if (Ethernet.linkStatus() == LinkOFF) {
			Serial.println("Ethernet cable is not connected.");
		}

		// start the server
		etherServer.begin();
		Serial.print("etherServer is at ");
		Serial.println(Ethernet.localIP());
		_etherClient = etherServer.available();
	}
	else {

		// check for the presence of the shield:
		if (WiFi.status() == WL_NO_SHIELD) {
			// Serial.println("WiFi shield not present");
			// don't continue:
			while (true);
		}

		String fv = WiFi.firmwareVersion();
		if (fv != "1.1.0") {
			// Serial.println("Please upgrade the Wifi firmware");
		}

		// attempt to connect to Wifi network:
		while (status != WL_CONNECTED) {
			// Serial.print("Attempting to connect to SSID: ");
			// Serial.println(ssid);
			// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
			status = WiFi.begin(ssid);

			// wait 10 seconds for connection:
			delay(10000);
		}
		wifiServer.begin();
		// you're connected now, so print out the status:
		PrintWifiStatus();
	}
}
void WebServerClass::CheckWebRequest() {
		String readString;
		if (serverTypeIsEthernet) {
			if (_etherClient) {
				if (_etherClient.connected()) {
					if (_etherClient.available()) {
						char c;
						//read char by char HTTP request
						while (readString.length() < HTML_MAX_LENGTH) {
							//store characters to string
							c = _etherClient.read();
							readString += c;
							if (c == '\n') break;
						}
					}
					WebServerClass::RouteRequest(readString);
					_etherClient.println(CreateHtmlPage());
					delay(1);   // ????
					_etherClient.stop();
					readString = "";
				}
			}
		}
		else {

			if (_wifiClient) {
				if (_wifiClient.connected()) {
					if (_wifiClient.available()) {
						char c;
						//read char by char HTTP request
						while (readString.length() < HTML_MAX_LENGTH) {
							//store characters to string
							c = _wifiClient.read();
							readString += c;
							if (c == '\n') break;
						}
					}
					RouteRequest(readString);
					_wifiClient.println(CreateHtmlPage());
					delay(1);   // ????
					_wifiClient.stop();
					readString = "";
				}
			}
		}
		//Clear the request
		readString = "";
	}
void WebServerClass::RouteRequest(String readString) {

		HashMap<String, String> callParams = BuildCallParams(readString);
		String action = callParams.valueFor(WEB_ACTION);
		action.toLowerCase();
		LogClass::WebRequest(action);
		if (action.compareTo(WEB_ACTION_SET_TIME) == 0) {
			UpdateDateTime(callParams.valueFor(WEB_DATE), callParams.valueFor(WEB_TIME));
		}
		else if (action.compareTo(WEB_ACTION_SHUTDOWN) == 0) {
			//_shutdownPointer;
		}
		else if (action.compareTo(WEB_ACTION_RESTART) == 0) {
			//_restartPointer;
		}
		else if (action.compareTo(WEB_ACTION_DOWNLOAD) == 0) {
			String fileName = callParams.valueFor(WEB_FILENAME);
			DownloadFromClient(fileName);
		}
		else if (action.compareTo(WEB_ACTION_UPLOAD) == 0) {
			String fileName = callParams.valueFor(WEB_FILENAME);
			UploadToClient(fileName);
		}
		else {
			LogClass::WebAction(WEB_ACTION_INVALID);
			Send404(callParams);
		}
	}

SDFile WebServerClass::UploadToClient(String fileName) {
		SDFile file = OpenSDFile(fileName, O_READ);
		if (serverTypeIsEthernet) {
			_etherClient.println("Content-Type: application/octet-stream");
			_etherClient.println();
		}
		else {
			_wifiClient.println("Content-Type: application/octet-stream");
			_wifiClient.println();
		}
		char file_buffer[16];
		int avail;
		while (avail == file.available()) {
			int to_read = min(avail, 16);
			if (to_read != file.read(file_buffer, to_read)) {
				break;
			}
			_etherClient.write(file_buffer, to_read);
			if (serverTypeIsEthernet) {
				_etherClient.write(file_buffer, to_read);
			}
			else {
				_wifiClient.write(file_buffer, to_read);
			}
		}
		file.close();
		return file;
	}
void WebServerClass::Send404(HashMap<String, String> callParams) {

	}
SDFile WebServerClass::OpenSDFile(String fileName, int readWrite) {
		SDFile file = SD.open(fileName, readWrite);
		if (file == 0) {  // Opening the file with return code of 0 is an error in SDFile.open
			FileNotFound(fileName);
		}
		return file;
	}
void WebServerClass::FileNotFound(String fileName) {
	String message = WEB_MESSAGE_FILE;
	message.replace("@Error", WEB_MESSAGE_NOT_FOUND);
	message.replace("@FIleName", fileName);
}

WebServerClass WebServer;

