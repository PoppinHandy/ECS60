#ifndef _QUEUE_H
#define _QUEUE_H

#include "scheduler.h"

class Queue
{
    public:
        Queue() { makeEmpty(); }
        void makeEmpty( );
        int dequeue( );
        bool isEmpty();
        void enqueue( int x );
        int theArray[ 100000 ];

    private:
        int            currentSize;
        int            front;
        int            back;
};


#endif
