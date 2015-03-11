#include "Queue.h"
#include <iostream>
void Queue::makeEmpty( )
{
  currentSize = 0;
  front = 0;
  back = -1;
}

bool Queue::isEmpty() {
    return currentSize == 0;
}

int Queue::dequeue( )
{
  currentSize--;
  int frontItem = theArray[ front ];
  std::cout << "front item: " << frontItem << std::endl;
  front++;
  return frontItem;
}

void Queue::enqueue( int x )
{
  back++;
  theArray[ back ] = x;
  currentSize++;
}

