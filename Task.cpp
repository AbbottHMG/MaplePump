// 
// 
// 

#include "Task.h"

TaskClass::TaskClass() { TaskClass::resetMe(); }

void TaskClass::resetMe() {
	TaskClass::_fPointer = NULL;
	TaskClass::_functionName = EnumsClass::Unkown;
	TaskClass::_period = 9999;
	TaskClass::_notInUse = true;
	TaskClass::_useCount = 0;
	TaskClass::_lastInvoke = millis();
}
void TaskClass::fInit(fPointer pointer,
				EnumsClass::Interrupt functionName,
				unsigned long period,
				int useCount)
{
	TaskClass::_fPointer = pointer;
	TaskClass::_functionName = functionName;
	TaskClass::_period = period;
	TaskClass::_notInUse = false;
	TaskClass::_lastInvoke = millis();
	TaskClass::_useCount = useCount;
}

EnumsClass::Interrupt TaskClass::functionName() {
	return TaskClass::_functionName;
}
bool TaskClass::completed() {
	return TaskClass::_useCount <= 0;
}
bool TaskClass::canRunTask() {
	unsigned long millisNow = millis();
	bool canRun = TaskClass::_useCount > 0 &&
		TaskClass::_lastInvoke + TaskClass::_period <= millisNow;
	return canRun;
}

bool TaskClass::runTask(TaskClass* task) {
	_useCount--;  // TODO: should useCount mgmt be auto or logically controlled in task function ?

	_fPointer(task);
}

void TaskClass::setUseCount(int useCount) {
	TaskClass::_useCount = useCount;
}


void TaskClass::printMe(String about) {
	if (about != "") {
		Serial.print(about);
		Serial.print(":");
	}
	Serial.print(EnumsClass::EnumStr(TaskClass::_functionName)); 
	Serial.print("-");
	Serial.print(TaskClass::_period);
	Serial.print("-");
	Serial.print(TaskClass::_useCount);
	Serial.print("-");
	Serial.println(_lastInvoke);
}

bool TaskClass::notInUse() {
	return TaskClass::_notInUse;
}

int TaskClass::useCount() {
	return _useCount;
}

TaskClass Task;

