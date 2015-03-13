#include "Queue.h"
#include <iostream>
using namespace std;

void Queue::makeEmpty( )
{
    currentSize = 0;
    front = 0;
    back = -1;
    for (int i = 0; i < 100000; ++i) {
        theArray[i] = 0;
        //cout << theArray[i] << endl;
    }
}

bool Queue::isEmpty() {
    return front==back;
}

int Queue::dequeue( )
{
    currentSize--;
    int frontItem = theArray[ front ];
    front++;
    return frontItem;
}

void Queue::enqueue( int x )
{
    back++;
    theArray[ back ] = x;
    currentSize++;
}
