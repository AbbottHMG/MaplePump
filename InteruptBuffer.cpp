// 
// 
// 

#include "InteruptBuffer.h"

void InteruptBufferClass::init()
{
	InteruptBufferClass::interuptBuffer.clear();
}
	// FIFO peek at head
	InteruptorClass InteruptBufferClass::peek(){
		return  InteruptBufferClass::interuptBuffer.first();
	}
	// FIFO pop head
	InteruptorClass InteruptBufferClass::pop(){
		return  InteruptBufferClass::interuptBuffer.pop();
	}
	// LIFO pull from tail
	InteruptorClass InteruptBufferClass::pull(){
		return  InteruptBufferClass::interuptBuffer.last();
	}
	// FIFO push into tail
	bool InteruptBufferClass::push(InteruptorClass interuptor){
		bool overflow = false;
		overflow = InteruptBufferClass::interuptBuffer.push(interuptor);
		return overflow;
	}
	// FIFO Push high priority action to head
	bool InteruptBufferClass::pushhead(InteruptorClass interuptor){
		bool overflow = false;
		overflow = InteruptBufferClass::interuptBuffer.unshift(interuptor);
		return overflow;
	}
	// Get number of enries
	int InteruptBufferClass::size(){
		return InteruptBufferClass::interuptBuffer.size();
	}

InteruptBufferClass InteruptBuffer;

