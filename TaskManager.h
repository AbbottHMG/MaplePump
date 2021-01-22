// TaskManager.h

#ifndef _TASKMANAGER_h
#define _TASKMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include<CircularBuffer.h>
#include <TimerThree.h>
#include <TimerOne.h>
#include "DefinedValues.h"
#include "Enums.h"
#include "FlowMeter.h"
#include "SapLines.h"
#include "Task.h"

typedef void (*fPointer)(TaskClass* task);
extern CircularBuffer<TaskClass*, InterruptBufferSize> CBuffer;
extern TaskClass Tasks[InterruptBufferSize];
class TaskManagerClass
{
 protected:
	 static TaskClass* peek();
	 static TaskClass* pop();
	 static bool fifoPush(TaskClass* task);
	 static bool lifoPush(TaskClass* task);
	 static fPointer _fPointer;
	 // For tests
	 static bool boolIsTrue();
	 static bool NoTaskPresent(EnumsClass::Interrupt functionName);
 public:
	 static void init();
	 static TaskClass* getAvailableTask();;
	 static bool runNextTask();
	 static bool hasTasks();
	 static int taskCount();
	 static void ShutOnOffSystem(TaskClass* callTask);
	 static void MinuteSensorInterrupt(void);
	 static void SecondSensorInterrupt(void);
	 static void MinuteSensorTest(TaskClass* task);
	 static void SecondSensorTest(TaskClass* task);
	 static void VacuumLostInitialize(TaskClass* task);
	 static void CheckSapLines(TaskClass* task);
	 //static void listArray();
	 static void listBuffer();
	 // For Testing
	 //static void BuildStaticTest();
	 //static void RunStaticTest();
	 //static bool testFunction(TaskClass* task);

};

extern TaskManagerClass TaskManager;

#endif

