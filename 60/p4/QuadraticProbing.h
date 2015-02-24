#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include "vector.h"
#include "mystring.h"
#include "familyRunner.h"

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//               and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
// int hash( String str, int tableSize )
//                        --> Static method to hash strings

class Person2{
 public:
  Person2();
  Person2( Person &p);
  //void setParent(Person2 &p1, Person2 &p2);
  Person person;
  int parent1;
  int parent2;
  int id;
};

class QuadraticHashTable
{
 public:
  QuadraticHashTable( const Person2 &p, int size);
  /*explicit QuadraticHashTable( const Person2 & notFound, int size = 101 );
 QuadraticHashTable( const Person2 & rhs )
   : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
   array( rhs.array ), currentSize( rhs.currentSize ) { }*/

  //int find( const Person2 & x ) const;

  void makeEmpty( );
  void displayHashTable( int x, int y);
  int insert( Person2 & x );
  //void remove( const HashedObj & x );
  const Person2 & findIndex(int index) const;
  const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

  //enum EntryType { ACTIVE, EMPTY, DELETED };
 private:
  /*struct HashEntry
  {
    HashedObj element;
    EntryType info;

  HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
  : element( e ), info( i ) { }
  };*/

  vector<Person2> array;
  int currentSize;
  //const HashedObj ITEM_NOT_FOUND;
  //bool isPrime( int n ) const;
  //int nextPrime( int n ) const;
  bool isActive( int currentPos ) const;
  int findPos( Person2 & p ) const;
  //int hash( const string & key, int tableSize ) const;
  int hash( Person2 & p, int tableSize ) const;
  //void rehash( );
};


#endif
