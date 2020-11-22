// 
// 
// 

#include "DefinedValues.h"
#include "LCD.h"

	// LCD Constants
static const uint8_t _lcd_addr = 0x27;
static const uint8_t _lcd_cols = 16;
static const uint8_t _lcd_rows = 2;

static unsigned long nextLineTestTime;
static unsigned long networkTime;
static bool InFreezingState;
static LiquidCrystal_I2C* lcd;
static bool LCD_Attached = LCD_ATTACHED;

		void LCDClass::PrintLn(String message, int rowNo = 0) {
			if (LCD_Attached) {
				if (rowNo == 0) {
					lcd->setCursor(0, 0);
				}
				else {
					lcd->setCursor(0, 1);
				}
				lcd->print(message);
			}
			else {
				Serial.println(message);
			}
		}
		void LCDClass::Init() {
			lcd = new LiquidCrystal_I2C(_lcd_addr, _lcd_cols, _lcd_rows);
			lcd->begin(2, 16);
			// Turn on the blacklight and print a message.
			lcd->backlight();
			lcd->clear();
			lcd->print(START_MSG);
		}

LCDClass LCD;

