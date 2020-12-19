// InteruptBuffer.h

#ifndef _INTERUPTBUFFER_h
#define _INTERUPTBUFFER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enms.h"
#include "Interuptor.h"
#include <CircularBuffer.h>
const int BufferSize = 20;
class InteruptBufferClass
{
 protected:

public:
	static  CircularBuffer<InteruptorClass, BufferSize> interuptBuffer;
	static void init();
	static InteruptorClass peek();
	static InteruptorClass pop();
	static InteruptorClass pull();
	static bool push(InteruptorClass interuptor);
	static bool pushhead(InteruptorClass interuptor);
	static int size();
};

extern InteruptBufferClass InteruptBuffer;

#endif

