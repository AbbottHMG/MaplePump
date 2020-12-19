
#pragma once
#include "Enms.h"
class InteruptInfo {
	typedef void (*fPointer)();
public:
	InteruptInfo(void (*fPointer)(),
		long cycle,
		int repeats,
		EnumsClass::Interupt interupt) {
		_fPointer = fPointer;
		_cycle = cycle;
		_repeats = repeats;
		_interupt = interupt;
	}
	~InteruptInfo() {};

	bool canRunFunction() {
		if((millis() >= _lastMillis + _cycle) && 
			_repeatCount <= _repeats){
			_repeatCount++;
			_lastMillis = millis();
			return true;
		}
		else{
		return false;}
	}

	bool canInteruptInfoBeDeleted(){
		return _repeatCount <= _repeats;
	}

	EnumsClass::Interupt Interupt(){
		return _interupt;
	} 
	void runInterupt(){
		_fPointer;
	}
private:
	EnumsClass::Interupt _interupt;
	long _lastMillis;
	long _cycle;
	int _repeats ;
	int _repeatCount = 0;
	fPointer _fPointer;
};
