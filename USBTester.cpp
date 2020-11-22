// 
// 
// 

#include "DefinedValues.h"
#include "USBTester.h"

bool IsUSBPowered() {
	int voltageLevel = analogRead(PINS_USB_ANALOG);
	return (voltageLevel < 310);
}

USBTesterClass USBTester;

