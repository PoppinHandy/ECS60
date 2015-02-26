#ifndef _PERSONQUEUE_H
#define _PERSONQUEUE_H

#include "QuadraticProbing.h"

// Queue class -- array implementation
//
// CONSTRUCTION: with or without a capacity; default is 10
//
// ******************PUBLIC OPERATIONS*********************
// void enqueue( x )      --> Insert x
// void dequeue( )        --> Return and remove least recently inserted item
// Object getFront( )     --> Return least recently inserted item
// bool isEmpty( )        --> Return true if empty; else false
// bool isFull( )         --> Return true if full; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Overflow and Underflow thrown as needed

class PersonQueue
{
 public:
  PersonQueue();



  void makeEmpty( );
  Person2 dequeue( );
  void enqueue( const Person2 & x );
  Person2 theArray[ 100000 ];

 private:
  int            currentSize;
  int            front;
  int            back;
};


#endif
