// 
// 
// 

#include "InteruptBuffer.h"

void InteruptBufferClass::init()
{
	buffer.clear();
}
	// FIFO peek at head
	EnumsClass::Interrupt InteruptBufferClass::peek(){
		return  buffer.first();
	}
	// FIFO pop head
	EnumsClass::Interrupt InteruptBufferClass::pop(){
		return  buffer.pop();
	}
	// LIFO pull from tail
	EnumsClass::Interrupt InteruptBufferClass::pull(){
		return  buffer.last();
	}
	// FIFO push into tail
	bool InteruptBufferClass::push(EnumsClass::Interrupt action){
		bool overflow = false;
		overflow = buffer.push(action);
		return overflow;
	}
	// FIFO Push high priority action to head
	bool InteruptBufferClass::pushhead(EnumsClass::Interrupt action){
		bool overflow = false;
		overflow = buffer.unshift(action);
		return overflow;
	}
	// Get number of enries
	int InteruptBufferClass::size(){
		return buffer.size();
	}

InteruptBufferClass InteruptBuffer;

