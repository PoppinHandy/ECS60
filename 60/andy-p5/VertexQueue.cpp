#include "VertexQueue.h"

/**
 * Construct the queue.
 */
VertexQueue::VertexQueue()
{
  theArray = new Vertex [100];
  makeEmpty( );
}

/**
 * Test if the queue is logically empty.
 * Return true if empty, false otherwise.
 */
bool VertexQueue::isEmpty( ) const
{
  return currentSize == 0;
}

/**
 * Make the queue logically empty.
 */
void VertexQueue::makeEmpty( )
{
  currentSize = 0;
  front = 0;
  back = -1;
}

/**
 * Get the least recently inserted item in the queue.
 * Return the least recently inserted item in the queue
 * or throw Underflow if empty.
 */
const Vertex & VertexQueue::getFront( ) const
{
  if( isEmpty( ) )
    throw Underflow( );
  return theArray[ front ];
}

/**
 * Return and remove the least recently inserted item from the queue.
 * Throw Underflow if empty.
 */
Vertex VertexQueue::dequeue( )
{
  if( isEmpty( ) )
    throw Underflow( );

  currentSize--;
  Vertex frontItem = theArray[ front ];
  increment( front );
  return frontItem;
}

/**
 * Insert x into the queue.
 * Throw Overflow if queue is full
 */
void VertexQueue::enqueue( const Vertex & x )
{
  increment( back );
  theArray[ back ] = x;
  currentSize++;
}

/**
 * Internal method to increment x with wraparound.
 */
void VertexQueue::increment( int & x )
{
  if( ++x == 9999 )
    x = 0;
}
