#ifndef FAMILYTREE_H
#define	FAMILYTREE_H

#include "familyRunner.h"
#include "QuadraticProbing.h"
#include "PersonQueue.h"

class FamilyTree {
  
 public:
  FamilyTree(Family *families, int familyCount);
  void runQueries(Query *queries, Person *answers, int queryCount);
  QuadraticHashTable hashTable;
  Person2 & getAncestor(PersonQueue &a, int a_size, PersonQueue &b, int b_size);
  void convertPerson2 (Person2 &x, Person &y);
};

#endif	/* FAMILYTREE_H */

