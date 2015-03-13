#ifndef _VERTEXQUEUE_H
#define _VERTEXQUEUE_H

#include "scheduler.h"
#include "dsexceptions.h"
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

class VertexQueue
{
 public:
  VertexQueue( );

  bool isEmpty( ) const;
  const Vertex & getFront( ) const;

  void makeEmpty( );
  Vertex dequeue( );
  void enqueue( const Vertex & x );
  Vertex *theArray;

 private:
  int            currentSize;
  int            front;
  int            back;

  void increment( int & x );
};

#endif
