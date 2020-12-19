// 
// 
// 

#include "Interupts.h"

void InteruptsClass::init()
{


}


void InteruptsClass::push(InteruptorClass interuptor){
	InteruptBufferClass::push(interuptor);
}

int InteruptsClass::interuptCount(){
		return InteruptBufferClass::size();	
}

void InteruptsClass::priority(InteruptorClass interuptor){
	InteruptBufferClass::pushhead(interuptor);
}

bool InteruptsClass::hasInterupts(){
	int interruptCount = InteruptBufferClass::size();
	return (interruptCount > 0);
}

InteruptorClass InteruptsClass::runNextInterupt()
{
	InteruptorClass interuptor  = InteruptBufferClass::peek();
	if(interuptor.canRunFunction()){
		interuptor.runInterupt();
		if(interuptor.canInteruptInfoBeDeleted()){
			InteruptBufferClass::pop();
		}
	}
	else 
	{
	// do nothimg
	}
}


InteruptsClass Interrupts;

