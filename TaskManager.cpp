

/* This is the crux of the interrupt handling - aside from the interrups themseleves.
* It LOOKS at the next task and sees if it should be run.
* If so, the associated task-function is run (which updates the usage count in the task)
* If the the count is 0, the task is poped (removed) from the CB.
*	It is then reset, so that it's available for the next thrown interrupt
*/
/*
 InterruptHandler is responsible for handling all the timed interupts
	and calling related tasks associated with those interrupts
	There are 2 timed interrupts 1 minute and 1 second
	1 Minutes is used for testing most sensors:
		sap line vacuum
		outside temperature
	1 second is used for time critical events:
		inside temperature (the heater heats up quickly)
		Sap tank state (full/empty). we don't want overflow

	Sap Line interrupt function runs a task the fetermines if the
		sap lines need testing, if so the tap line test function
		turns ofl all the line valves and cycles thru each line.

	Outside termperature determines if the pump shoul be on
		or off
	Inside temperature is monitrored when the unit is shut down (too cold outside)
*/

#include "TaskManager.h"

void TaskManagerClass::init()
{
	Serial.println("Initialize Tasks - ");

	for (int i = 0; i > InterruptBufferSize; i++) {
		Tasks[i] = TaskClass();
	}
	Serial.println(InterruptBufferSize);
	// Now start interrupt handling
	Timer1.initialize(Timer_Sec);
	Timer1.attachInterrupt(TaskManagerClass::SecondSensorInterrupt);
	Timer3.initialize(Timer_Min);
	Timer3.attachInterrupt(TaskManagerClass::MinuteSensorInterrupt);
}


// Does the CB have any tasks
bool TaskManagerClass::hasTasks() {
	return !CBuffer.isEmpty();
}


// available tasks are selected from the task array
// when a new interrupt is raised
TaskClass* TaskManagerClass::getAvailableTask() {
	for (int i = 0; i < InterruptBufferSize; i++) {
		if (Tasks[i].notInUse()) {
			return &Tasks[i];
		}
	}
}

bool TaskManagerClass::runNextTask()
{
	bool noMoreTasks = false;
	int size = CBuffer.size();
	if (CBuffer.size() > 0) {
		TaskClass* task = TaskManagerClass::peek();
		if (task->canRunTask()) {
			task->runTask(task);
			task->printMe("Run Next Task - ");
			if (task->completed()) {
				task = TaskManagerClass::pop();
				task->resetMe();
			}
			//TaskManagerClass::listBuffer();
		}
		else
		{
			// do nothimg -  waiting for period to elapse 
		}
	}
	else {
		noMoreTasks = true;
	}
	return noMoreTasks;
}
#pragma region CBuffer routines
// gets next  task on CB (leaves in place)
TaskClass* TaskManagerClass::peek() {
	return CBuffer.last();
}
// pops (removes) the next available task from CB
TaskClass* TaskManagerClass::pop() {
	return CBuffer.pop();
}
// puts task at end of CB (the first to be popped)
bool TaskManagerClass::fifoPush(TaskClass * task) {
	return CBuffer.unshift(task);
}
// puts task at front of CB (the last to be popped)
bool TaskManagerClass::lifoPush(TaskClass * task) {
	CBuffer.push(task);
}
int TaskManagerClass::taskCount() {
	return CBuffer.size();

}
#pragma endregion CBuffer routines

bool TaskManagerClass::boolIsTrue() {
	return rand() % 2 == 1;
}


// Used to emulate singleton
// stops creation of duplicate task types
bool TaskManagerClass::NoTaskPresent(EnumsClass::Interrupt functionName) {
	bool noTaskPresent = true;
	for (int i = 0; i < CBuffer.size(); i++) {
		if (CBuffer[i]->functionName() == functionName){
			noTaskPresent = false;
			}
	}
	return noTaskPresent;
}

bool sapLinesTestInprogress;
fPointer pointer;
void TaskManagerClass::SecondSensorInterrupt(void) {
	noInterrupts();
	if (TaskManagerClass::NoTaskPresent(EnumsClass::CheckSecSensors)) {
		TaskClass* task = TaskManagerClass::getAvailableTask();
		pointer = SecondSensorTest;
		task->fInit(pointer, EnumsClass::CheckSecSensors, Millis_Tenth_Sec);
		task->printMe("New Second Interupt");
		TaskManagerClass::fifoPush(task);
	}
	interrupts();
}
void TaskManagerClass::SecondSensorTest(TaskClass* callTask) {
	// Always process flow rate slice
	noInterrupts();
	FlowMeterClass::ProcessSlice();
	interrupts();
	// Checks inside temp and sap tank float
		callTask->printMe("Second Called");
	Serial.println("Float-InHeat Test");
	if (TaskManagerClass::boolIsTrue()) { // float has changed to high/low
		// call float class
		Serial.println("Float High/Low");
		
	}
	if (TaskManagerClass::boolIsTrue()) { // temp has changed to high/low
		// call float class
		Serial.println("In Temperature High/Low");
	}
}
void TaskManagerClass::MinuteSensorInterrupt(void) {
	noInterrupts();
	if (TaskManagerClass::NoTaskPresent(EnumsClass::CheckMinSensors)) {	
		TaskClass* task = TaskManagerClass::getAvailableTask();
		pointer = MinuteSensorTest;
		task->fInit(pointer, EnumsClass::CheckMinSensors, Millis_5Sec);
		task->printMe("New Minute Interupt");
		TaskManagerClass::fifoPush(task);
	}
	interrupts();
}
void TaskManagerClass::MinuteSensorTest(TaskClass* callTask) {
	// Checks vacuum, outside temp and sap flow
	Serial.println("MinuteSensorTest");
	callTask->printMe("Minute Called");
	if(!sapLinesTestInprogress){
		Serial.println("No Sapline Test Currently In Progress"); 
		if (TaskManagerClass::NoTaskPresent(EnumsClass::InitializeVacuumTest)) {
			if (TaskManagerClass::boolIsTrue()) { // vacuum lost
				Serial.println("Vacuum, Lost");
				sapLinesTestInprogress = true;
				Serial.println("Sapline Test started");
				TaskClass* minTask = TaskManagerClass::getAvailableTask();
				pointer = VacuumLostInitialize;
				minTask->fInit(pointer, EnumsClass::InitializeVacuumTest, Millis_10Sec);
				minTask->printMe("Initializing vacuum lost");
				TaskManagerClass::fifoPush(minTask);
			}
			else {
				Serial.println("Vacuum is strong");
			}
		}
	}
	else {
		Serial.println("SapLine Tests already in process");
	}
	if (TaskManagerClass::boolIsTrue()) { // outside temp change
		// stop or start system
		if (TaskManagerClass::NoTaskPresent(EnumsClass::ShutOnOffSystem)) {
			TaskClass* task = TaskManagerClass::getAvailableTask();
			pointer = ShutOnOffSystem;
			task->fInit(pointer, EnumsClass::ShutOnOffSystem, Millis_Sec);
			task->printMe("Shut On Off");
			TaskManagerClass::fifoPush(task);
		}
	}
	if(TaskManagerClass::boolIsTrue()){ // running + open + no sap flow - we have a problem
		// what to do? What to do?
	 }
}
void TaskManagerClass::VacuumLostInitialize(TaskClass* callTask) {
	// Close all lines & wait 10 seconds

	callTask->printMe("Vacuum Lost Shut Lines");
	if (TaskManagerClass::NoTaskPresent(EnumsClass::CheckSapLines)) {
		TaskClass* task = TaskManagerClass::getAvailableTask();
		pointer = CheckSapLines;
		task->fInit(pointer, EnumsClass::CheckSapLines, Millis_10Sec, SapLineCount);
		task->printMe("Sap Line count - 8 - ");
		TaskManagerClass::fifoPush(task);
	}
}

void TaskManagerClass::ShutOnOffSystem(TaskClass* callTask) {
	Serial.print("Sut the thing on/off - ");
	callTask->printMe();
}
void TaskManagerClass::CheckSapLines(TaskClass* task) {	
	// In this case we update task count and leave it in buffer
	// Test Sapline(usecount - rel to 0)
	// NOTE - Use Count is decremented each time the task function is run
	task->printMe("Check Sap Lines");
	if (task->completed()) {
		sapLinesTestInprogress = false;
		return;
	}
	Serial.print("SapLine -  ");
	Serial.print(task->useCount());
	if (TaskManagerClass::boolIsTrue()) {
		Serial.println(" is good");
	}
	else {
		Serial.println(" is open");
	}
}

#pragma region Test routines
// Test Stufff


//bool TaskManagerClass::testFunction(TaskClass* task) {
//	// TODO: useCount could be done here ?
//	task->printMe("testFunct");
//}
//
//void TaskManagerClass::BuildStaticTest() {
//	Serial.println("");
//	int order = 0;
//	TaskClass* task;
//	TaskClass* cbTask;
//	fPointer tPointer;
//	tPointer = TaskManagerClass::testFunction;
//
//	task = TaskManagerClass::getAvailableTask();
//	task->init(tPointer, EnumsClass::CheckInTemp, EnumsClass::FifoPush, Mills_10Sec);
//	TaskManagerClass::fifoPush(task);
//	Serial.print("buffer size = ");
//	Serial.println(CBuffer.size());
//	task = TaskManagerClass::peek();
//	task->printMe("+");
//
//	task = TaskManagerClass::getAvailableTask();
//	task->init(fPointer, EnumsClass::CheckMinSensors, EnumsClass::LifoPush, Mills_5Sec); TaskManagerClass::lifoPush(task);
//	task = TaskManagerClass::peek();
//	task->printMe("+");
//
//	task = TaskManagerClass::getAvailableTask();
//	task->init(fPointer, EnumsClass::CheckSapFloat, EnumsClass::FifoPush, Mills_Sec);
//	TaskManagerClass::fifoPush(task);
//	task = TaskManagerClass::peek();
//	task->printMe("+");
//
//	TaskManagerClass::listArray();
//	TaskManagerClass::listBuffer();
//	Serial.println("Test Queue complete");
//}
//void TaskManagerClass::RunStaticTest() {
//	Serial.println("Run Static test");
//	while (CBuffer.size() > 0) {
//		TaskClass* task = CBuffer.pop();
//		task->runTask(task);
//		delete task;
//		TaskManagerClass::listBuffer();
//	}
//}

// Note - I'm using _period to indicate expected order of popping
void TaskManagerClass::listBuffer() {
	TaskClass* task;
	Serial.print("List Buffer Size = ");
	Serial.println(CBuffer.size());
	for (int i = 0; i < CBuffer.size(); i++) {
		task = CBuffer[i];
		task->printMe();
	}
}
//void TaskManagerClass::listArray() {
//	Serial.print("List array - size = ");
//	Serial.println(InterruptBufferSize);
//	for (int i = 0; i < InterruptBufferSize; i++) {
//		TaskClass* task = &Tasks[i];
//		task->printMe();
//	}
//}

#pragma endregion Test routines

TaskManagerClass TaskManager;

