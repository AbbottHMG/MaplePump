// 
// 
// 

#include "Callback.h"

void CallbackClass::init(long millisWait)
{
	_millisLast = millis();
	_millisWait = millisWait;
}

// This is called if the callback runs and is finished processing
void CallbackClass::popBuffer(){
	InteruptBufferClass::pop();			
}
bool CallbackClass::okToRun()
{
	bool OkToRun = false;
	if(_millisLast >0){
		if(_millisLast + _millisWait >= millis()){
			_millisLast = millis();
			OkToRun = true;
		}
	}
	return OkToRun;
}
void run(){
}

CallbackClass Callback;

