// 
// 
// 

#include "Interuptor.h"

void InteruptorClass::init(void (*fPointer)(),
		long cycle,
		int repeats,
		EnumsClass::Interupt interupt)
{
		_fPointer = fPointer;
		_cycle = cycle;
		_repeats = repeats;
		_interupt = interupt;
}

	bool InteruptorClass::canRunFunction() {
		if((millis() >= _lastMillis + _cycle) && 
			_repeatCount <= _repeats){
			_repeatCount++;
			_lastMillis = millis();
			return true;
		}
		else{
		return false;}
	}

	
	bool InteruptorClass::canInteruptInfoBeDeleted(){
		return _repeatCount <= _repeats;
	}

	EnumsClass::Interupt InteruptorClass::Interupt(){
		return _interupt;
	} 
	void InteruptorClass::runInterupt(){
		_fPointer;
	}
InteruptorClass Interuptor;

