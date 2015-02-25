#ifndef FAMILYTREE_H
#define	FAMILYTREE_H

#include "familyRunner.h"
#include "QuadraticProbing.h"
#include "QueueAr.h"

class FamilyTree {
  
 public:
  FamilyTree(Family *families, int familyCount);
  void runQueries(Query *queries, Person *answers, int queryCount);
  QuadraticHashTable hashTable;
  Person2 & getAncestor(Queue <Person2> &a, int a_size, Queue <Person2> &b, int b_size);
  void convertPerson2 (Person2 &x, Person &y);
};

#endif	/* FAMILYTREE_H */

