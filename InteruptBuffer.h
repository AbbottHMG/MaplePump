// InteruptBuffer.h

#ifndef _INTERUPTBUFFER_h
#define _INTERUPTBUFFER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enms.h"
#include <CircularBuffer.h>
const int BufferSize = 20;
class InteruptBufferClass
{
 protected:

 public:
	static  CircularBuffer<EnumsClass::Interrupt, BufferSize> buffer;
	static void init();
	static EnumsClass::Interrupt peek();
	static EnumsClass::Interrupt pop();
	static EnumsClass::Interrupt pull();
	static bool push(EnumsClass::Interrupt action);
	static bool pushhead(EnumsClass::Interrupt action);
	static int size();
};

extern InteruptBufferClass InteruptBuffer;

#endif

