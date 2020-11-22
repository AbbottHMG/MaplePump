// 
// 
// 

#include "RTClock.h"


static unsigned long lastMillisCheck;
static RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };


	void RTClockClass::Init() {
		rtc.begin();

		if (!rtc.isrunning()) {
			Serial.println("RTC is NOT running!");
			// following line sets the RTC to the date & time this sketch was compiled
			rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
			// This line sets the RTC with an explicit date & time, for example to set
			// January 21, 2014 at 3am you would call:
			// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
		}
	}
	bool RTClockClass::IsItTime(int waitMillis) {
		bool returnTimeOk = false;
		if (lastMillisCheck + waitMillis > millis()) {
			returnTimeOk = true;
			lastMillisCheck = millis();
		}
		return returnTimeOk;
	}
	void RTClockClass::ResetDateTime(char* date, char* time) {
		rtc.adjust(DateTime(date, time));
	}
	String RTClockClass::GetTimeStamp(bool dateOnly) {
		DateTime time = rtc.now();
		String returnDateTime = time.timestamp(DateTime::TIMESTAMP_FULL);
		if (dateOnly) {
			String dateOnly = time.timestamp(DateTime::TIMESTAMP_DATE);
			dateOnly.replace("-", "");
			returnDateTime = dateOnly;
		}
		return returnDateTime;
	}
RTClockClass RTClock;

