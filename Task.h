// Task.h

#ifndef _TASK_h
#define _TASK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Enums.h"
#include "LCD.h"


class TaskClass
{
	typedef bool (*fPointer)(TaskClass* task);
	
 public:
	TaskClass();
	void fInit(fPointer pointer,
				EnumsClass::Interrupt functionName,
				unsigned long period,
				int useCount = 1);
	void printMe(String about = "");
	void resetMe();
	bool notInUse();
	bool completed();
	bool canRunTask();
	int useCount();
	bool runTask(TaskClass* task);
	void setPeriod(unsigned long period);
	void setUseCount(int useCount);
	EnumsClass::Interrupt functionName();
protected:

	EnumsClass::Interrupt _functionName;
	unsigned long _period; // wait time since last envoke
	unsigned long _lastInvoke;
	bool _notInUse;
	int _useCount = 0; // Managed by function - if 0 , task is removed from CB and set for reuse
	TaskClass::fPointer _fPointer;
};

extern TaskClass Task;

#endif

