#include "PersonQueue.h"

/**
 * Construct the queue.
 */

PersonQueue::PersonQueue( ) 
{
  makeEmpty( );
}

/**
 * Make the queue logically empty.
 */
void PersonQueue::makeEmpty( )
{
  currentSize = 0;
  front = 0;
  back = -1;
  for( int i = 0; i < 100000; i++ )
    {
      theArray[ i ].parent1 = 0;
      theArray[ i ].parent2 = 0;
      theArray[ i ].id = 0;
      theArray[ i ].person.year = -1;
    }
}

/**
 * Return and remove the least recently inserted item from the queue.
 * Throw Underflow if empty.
 */

Person2 PersonQueue::dequeue( )
{

  currentSize--;
  Person2 frontItem = theArray[ front ];
  front++;
  return frontItem;
}

/**
 * Insert x into the queue.
 * Throw Overflow if queue is full
 */

void PersonQueue::enqueue( const Person2 & x )
{
  back++;
  theArray[ back ] = x;
  currentSize++;
}

