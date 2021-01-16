// 
// 
// 

#include "FlowMeter.h"

	static volatile byte pulseCount;
	static float flowGals;
	static float totGals;
	static unsigned int flowMilliLitres;
	static unsigned long totalMilliLitres;
	static unsigned long oldTime;
	static float flowRate;

void FlowMeterClass::pulseCounter()
{
	// Increment the pulse counter
	cli();//stop interrupts 
	pulseCount++;
	sei();//allow interrupts
}
void FlowMeterClass::Init() {	

		// Set up the status LED line as an output
		pinMode(PINS_FLOW_STATUS_LED, OUTPUT);
		digitalWrite(PINS_FLOW_STATUS_LED, HIGH);  // We have an active-low LED attached

		pinMode(PINS_FLOW_SENSOR, INPUT);
		digitalWrite(PINS_FLOW_SENSOR, HIGH);

		pulseCount = 0;
		flowRate = 0.0;
		flowMilliLitres = 0;
		totalMilliLitres = 0;
		oldTime = 0;
		flowGals = 0;
		totGals = 0;
		// The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
		// Configured to trigger on a FALLING state change (transition from HIGH
		// state to LOW state)
		// We don't need interrupts, process slice called with all other interrupt functions
		// InterruptsClass::AttachInterrupt(FLOW_SENSOR_INTERRUPT, pulseCounter, FALLING);

	}
void FlowMeterClass::ProcessSlice() {

	// Disable interrupt before calculating flow rate and sending the value to
	// the host


	// Because this loop may not complete in exactly 1 second intervals we calculate
	// the number of milliseconds that have passed since the last execution and use
	// that to scale the output. We also apply the calibrationFactor to scale the output
	// based on the number of pulses per second per units of measure (litres/minute in
	// this case) coming from the sensor.
	flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / FLOW_CALIBRATION_FACTOR;

	// Note the time this processing pass was executed. Note that because we've
	// disabled interrupts the millis() function won't actually be incrementing right
	// at this point, but it will still return the value it was set to just before
	// interrupts went away.
	oldTime = millis();

	// Divide the flow rate in litres/minute by 60 to determine how many litres have
	// passed through the sensor in this 1 second interval, then multiply by 1000 to
	// convert to millilitres.
	flowMilliLitres = (flowRate / 60) * 1000;
	// Add the millilitres passed in this second to the cumulative total
	totalMilliLitres += flowMilliLitres;
	flowGals = flowMilliLitres / FLOW_MIL_TO_GAL;
	totGals = totalMilliLitres / FLOW_MIL_TO_GAL;
	char tempC[8];
	dtostrf(flowMilliLitres, 8, 4, tempC);
	LogClass::FlowRate(String(tempC));
	dtostrf(totalMilliLitres, 8, 4, tempC);
	LogClass::FlowTot(String(tempC));

	// Reset the pulse counter so we can start incrementing again
	pulseCount = 0;

	// Enable the interrupts again now that we've finished sending output
}

float FlowMeterClass::FlowRate(){
	return flowRate;
}
FlowMeterClass FlowMeter;

