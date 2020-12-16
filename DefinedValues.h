// DefinedValues.h

#ifndef _DEFINEDVALUES_h
#define _DEFINEDVALUES_h

static const int RelayCount[] = {9, 3};
static const int ValveBypassPins[] = { 0, 24, 26};
static const int ValvePinsAll[] = { 0,30,32,34,36,38,40,42,44 };
static volatile bool Web_Is_Reading = false;
static volatile bool Web_Is_Writing = false;
static volatile bool Web_Read = false;
static volatile bool Web_Write = false;
static volatile bool CheckSensors = false;
static volatile bool ProcessTimedInterrupt = false;
static volatile bool TankFloatInterruptRaised = false;
#define LCD_ATTACHED false
// PINS
////Most Arduino designs have two hardware interrupts(referred to as "interrupt0" and "interrupt1") hard - wired to digital I / O pins 2 and 3, respectively.
////The Arduino Mega has six hardware interrupts including the additional interrupts("interrupt2" through "interrupt5") on pins 21, 20, 19, and 18.
#define	PINS_HEATER 49
#define	PINS_FLOAT_SWITCH 11 
#define PINS_FLOW_STATUS_LED 7  //???????????
#define PINS_FLOW_SENSOR 12   // 2 - interrupt0
#define PINS_SAP_TANK_PUMP 5  // ?????
#define PINS_SD_CARD 4
#define PINS_SD_CARD_SLAVE 10
#define PINS_TEMP_IN_ONE_WIRE 8
#define PINS_TEMP_OUT_ONE_WIRE 9
#define PINS_TEMP_OUT 4
#define PINS_USB_ANALOG 4 
#define PINS_VACUUM_ANALOG 3
#define PINS_VACUUM_PUMP 48  // ?????

//  Interrupt Intervals
	// Intervals are in minutes
// #define INTERVAL_FLOW 1  // Not used now
#define INTERVAL_HEATER_TEMPERATURE 1
#define INTERVAL_MINUTE_HALF_FACTOR 30000
#define INTERVAL_MINUTE_QUARTER_FACTOR 15000
#define INTERVAL_MINUTE_FACTOR 60000
#define INTERVAL_RESTART 1
#define INTERVAL_SECOND_FACTOR 1000
#define INTERVAL_SHUTDOWN 1
#define INTERVAL_TEMPERATURE 3
#define INTERVAL_LINE_ON_OFF_DELAY  2  // In seconds
#define INTERVAL_VACUUM 1
constexpr long Mills_Sec = 1000;
constexpr long Mills_5Sec = 5000;
constexpr long Mills_10Sec = 10000;
constexpr long Mills_Min = 60000;
constexpr long Mills_5Min = 300000;
constexpr long Timer_Milli = 1000;
constexpr long Timer_Tenth = 100000;
constexpr long Timer_Sec = 1000000;
constexpr long Timer_Min = 60000000;
constexpr long Timer_5Min = 300000000;

// Json defines
#define ARDUINOJSON_USE_DOUBLE 0
#define ESTIMATED_JSON_SIZE 2000

// LCD Labels
#define PRMPT_AT " @ "
#define PROMPT_TEMP "TempF:"
#define PRMPT_STATE "State:"
#define PRMPT_LINES "Valves:"
#define START_MSG "Vac:"
#define START_CLOSE_MSG "-Lines"

// Realtime Clock
#define DATE_ONLY true
#define DATE_TIME false

// Sap Flow  status
#define FLOW_SENSOR_INTERRUPT 0 // 0 = digital pin 2
#define FLOW_CALIBRATION_FACTOR 4.5
#define FLOW_INTERVAL 1000 // Interval between reads
#define FLOW_MIL_TO_GAL 3785.412 

// Sap Pump Values
#define PUMP_ONOFF_DELAY 5000
#define SAP_PUMP_ON "Pump On"
#define SAP_PUMP_OFF "Pump Off"
#define SAP_PUMPING "Pumping"

// Temperature Values
#define INSIDETEMP 0
#define OUTSIDETEMP 1

#define INSIDE_HIGHTEMP  42.0
#define INSIDE_LOWTEMP  32.1
#define INSIDE 0
#define OUTSIDE 1
#define OUTSIDE_HIGHTEMP  42.0
#define OUTSIDE_LOWTEMP  32.1
#define INIT_TEMP  true
#define TEST_TEMP  false
#define SET_HEATER_OFF  false
#define SET_HEATER_ON  true

// Timed Interrupts
#define INTERRUPT_INFOS_SIZE 20

// Vacuum
#define VACUUM_PUMP_DIGI 0  // ????
#define TESTLOOPLIMIT 4

// Vacuum Pump
#define BYPASS_VALVE_INDEX 1
#define PUMP_VALVE_INDEX 2
#define PUMP_ONOFF_DELAY 500
#define VACUUM_PUMP_DIGI 0  // ????
#define START_PUMP true
#define START_PUMP_NO false
#define VACUUM_PUMP_BASE_PSI 5.0

// Valves
#define VALVE_DELAY 500
#define LINE_VALVES 0
#define BYPASS_VALVES 1
 
// WebServer
#define WEB_ACTION "action"
#define WEB_ACTION_DOWNLOAD "download"
#define WEB_ACTION_INVALID "invalid"
#define WEB_ACTION_NONE "none"
#define WEB_ACTION_REFRESH "refresh"
#define WEB_ACTION_RESTART "restart"
#define WEB_ACTION_SET_TIME "settime"
#define WEB_ACTION_SHUTDOWN "shutdown"
#define WEB_ACTION_UPLOAD "upload"
#define WEB_DATE "date"
#define WEB_TIME "time"
#define WEB_FILENAME "filename"
#define WEB_SERVER_WIFI false
#define WEB_SERVER_ETHERNET true
#define WEB_SERVER_PORT 80
#define WEB_MESSAGE_DOWNLOAD "download to client"
#define WEB_MESSAGE_FILE "File @Error @Direction of @FileName - @Result"
#define WEB_MESSAGE_INVALID_ACTION "Unsupported Action - @Action"
#define WEB_MESSAGE_NOT_FOUND "not found -"
#define WEB_MESSAGE_UPLOAD "upload to server"
#define HTML_PAGE_NAME "vacupage"
#define HTML_MAX_LENGTH 1000
#endif

