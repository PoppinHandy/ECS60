#ifndef FAMILYTREE_H
#define	FAMILYTREE_H
#include "familyRunner.h"
#include "QuadraticProbing.h"

class FamilyTree {
  
 public:
  FamilyTree(Family *families, int familyCount);
  //void runQueries(Query *queries, Person *answers, int queryCount);
  QuadraticHashTable hashTable;

class FamilyTree {
  
public:
  FamilyTree(Family *families, int familyCount);
  void runQueries(Query *queries, Person *answers, int queryCount);

};

#endif	/* FAMILYTREE_H */
