#include "QuadraticProbing.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;
/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
/*template <class HashedObj>
bool QuadraticHashTable<HashedObj>::isPrime( int n ) const
{
  if( n == 2 || n == 3 )
    return true;

  if( n == 1 || n % 2 == 0 )
    return false;

  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;

  return true;
  }*/

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
/*
template <class HashedObj>
int QuadraticHashTable<HashedObj>::nextPrime( int n ) const
{
  if( n % 2 == 0 )
    n++;

  for( ; !isPrime( n ); n += 2 )
    ;

  return n;
}*/

Person2::Person2()
{
  person.year = -1;
  id = 0;
  parent1 = 0;
  parent2 = 0;
}

//Parent
Person2::Person2(Person &p):person(p)
{ 
  id = person.year;
  for (int i = 0; i < 12; i++)
    {
      id += int(person.firstName[i]);
      id += int(person.lastName[i]);
    }
  parent1 = 0;
  parent2 = 0;
  //cout << person.firstName << " id is " << id << endl;
}//end constructor

/*void Person2::setParent(int p1, int p2)
{
  parent1 = p1;
  parent2 = p2;
  }*/
/**
 * Construct the hash table.
 */
QuadraticHashTable::QuadraticHashTable(const Person2 &p, int size )
  : array( size )
{
  makeEmpty( );
}

/**
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */
int QuadraticHashTable::insert( Person2 & p )
{
  // Insert x as active
  int currentPos = hash(p, array.size());
  if (strcmp (p.person.firstName, array[currentPos].person.firstName) == 0 && strcmp (p.person.lastName, array[currentPos].person.lastName) == 0 && p.person.year == array[currentPos].person.year && array[currentPos].parent1 > 0 && array[currentPos].parent2 > 0 )
    {
      return currentPos;
    }
  while(array[currentPos].person.year != -1 && array[currentPos].parent1 > 0 && array[currentPos].parent2 > 0)
    {
      currentPos++;
      if (currentPos == currentSize)
	{
	  currentPos = 0;
	}
    }
  if(array[currentPos].parent1 == 0 || array[currentPos].person.year == -1 )
    {
      array[ currentPos ] = p;
      p.id = currentPos;
      return currentPos;
    }
  if( isActive( currentPos ) )
    {
      return currentPos;
    }
  return currentPos;
  // Rehash; see Section 5.5
  /*if( ++currentSize > array.size( ) / 2 )
    rehash( );*/
}

void QuadraticHashTable::displayHashTable(int x, int y)
{
  for (int i = x; i <= y; i++)
    {
      if(array[i].person.year != -1){
	cout << "Child: " << array[i].person.firstName  << " " << array[i].person.lastName << endl;
	cout << "Parent1: " << array[i].parent1 << endl;
	cout << "Parent2: " << array[i].parent2 << endl;
	cout << "Year: " << array[i].person.year << endl;
	cout << "ID: " << array[i].id << endl;
	cout << endl;
      }
    }
}
/**
 * Expand the hash table.
 */
/*template <class HashedObj>
void QuadraticHashTable<HashedObj>::rehash( )
{
  vector<HashEntry> oldArray = array;

  // Create new double-sized, empty table
  array.resize( nextPrime( 2 * oldArray.size( ) ) );
  for( int j = 0; j < array.size( ); j++ )
    array[ j ].info = EMPTY;

  // Copy table over
  currentSize = 0;
  for( int i = 0; i < oldArray.size( ); i++ )
    if( oldArray[ i ].info == ACTIVE )
      insert( oldArray[ i ].element );
      }*/

/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
int QuadraticHashTable::findPos( Person2 & p ) const
{
  /* 1*/      int collisionNum = 0;
  /* 2*/      int currentPos = hash( p, array.size( ) );
  /* 3*/      while( array[ currentPos ].person.year != -1 &&
		     array[ currentPos ].id != p.id )
    {
      /* 4*/          currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
      /* 5*/          if( currentPos >= array.size( ) )
	/* 6*/              currentPos -= array.size( );
    }
  /* 7*/      return currentPos;
}


/**
 * Find Person in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
const Person2 & QuadraticHashTable::findIndex(int index) const
{
  return array[index];
}

/**
 * Make the hash table logically empty.
 */
void QuadraticHashTable::makeEmpty()
{
  currentSize = 0;
  for( int i = 0; i < array.size( ); i++ )
    {
      array[ i ].parent1 = 0;
      array[ i ].parent2 = 0;
      array[ i ].id = 0;
      array[ i ].person.year = -1;

    }
}

/**
 * Deep copy.
 */
const QuadraticHashTable & QuadraticHashTable::
operator=( const QuadraticHashTable & rhs )
{
  if( this != &rhs )
    {
      array = rhs.array;
      currentSize = rhs.currentSize;
    }
  return *this;
}


/**
 * Return true if currentPos exists and is active.
 */
bool QuadraticHashTable::isActive( int currentPos ) const
{
  return array[ currentPos ].person.year > 0;
}

/**
 * A hash routine for string objects.
 */
/*int QuadraticHashTable<HashedObj>::hash( const string & key, int tableSize ) const
{
  int hashVal = 0;

  for( int i = 0; i < key.length( ); i++ )
    hashVal = 37 * hashVal + key[ i ];

  hashVal %= tableSize;
  if( hashVal < 0 )
    hashVal += tableSize;

  return hashVal;
  }*/
:

/**
 * A hash routine for ints.
 */
int QuadraticHashTable::hash( Person2 &p, int tableSize ) const
{
  return p.id % tableSize;
}
