/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 11/2020 Abbott Fleur - Added peek and pushheader funtion
 * Copyright (c) 2020 Abbott Fleur - Upgraded byte -> callback
 * Copyright (c) 2015 Daniel Eisterhold
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "FIFO_AF.h"

FIFO_AF::FIFO_AF()
 {
  head = 0;
  tail = 0;
  numElements = 0;
	 //// Serial.begin(115200);
	 //while (!// Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
}

FIFO_AF::~FIFO_AF() {
}

void FIFO_AF::clear(){
  head = 0;
  tail = 0;
  numElements = 0;
}

bool FIFO_AF::push(void (*callBack)()) {
	
	if(numElements >= FIFO_AF_SIZE) {
		// Serial.print("Buffer full");
	  return false;
    }

	//Increment size
	numElements++;

	//Only move the tail if there is more than one element
	if(numElements > 1) {
		//Increment tail location
		tail++;
    }
	//Store data into array
	buffer[tail] = callBack;
  	return true;
}

// Force the head element to the passed entry
// This shifts all entries backwards and inserts new entry at head (makes it highest priority)
bool FIFO_AF::pushheader(void (*callBack)()) { 
  if(numElements >= FIFO_AF_SIZE) {
    // Serial.print("Buffer full-");
  	// Serial.println(numElements);
      return false;
  }   
    //Increment size
    numElements++;

    //Only move the tail if there is more than one element
    if(numElements > 1) {
      //Increment tail location
      tail++;
    // Serial.print("Tail-"); // Serial.println(tail);
    }
  // ? Not sure how to deal with overflow ... this loses the last tail item
 
    // Serial.print("Head-"); // Serial.println(head);
    // Move all elements back 1 position
    for (int i = tail; i > head; i--) {
      buffer[i] = buffer[i-1]; // shift last element
    // Serial.print("i-"); // Serial.println(i);
	}
    //Store data into array
    buffer[head] = callBack;  // Insert new leader
}

function_pointer FIFO_AF::pop() {
  if(numElements == 0) {
    // Serial.print("Pop Buffer empty");
    return 0;
  }
  //Decrement size and tail pointer
  numElements--;
  tail--;
  function_pointer data = buffer[head];
  if(numElements >= 1) {
    // Move all elements down 1 position
    for (int i = head; i < tail; i++) {
      buffer[i+1] = buffer[i]; // shift element
    }
  }
  return data;
}

function_pointer FIFO_AF::peek() {
  if(numElements == 0) {
    // Serial.print("Peek Buffer empty");
    return 0;
  }
  function_pointer data = buffer[head];
  return data;
}

int FIFO_AF::size() { 
  return numElements;
}
void FIFO_AF::getBuffKeys(*char retString){
	
}