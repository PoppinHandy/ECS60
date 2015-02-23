// Author: Sean Davis

#include "familytree.h"

FamilyTree::FamilyTree(Family *families, int familyCount):hashTable(Person2(), 10000)
{
  for(int i = 0; i < familyCount; i++)
    {
      hashTable.insert(Person2(families[i].person));
    }
} // FamilyTree()

/*void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
  
}  // runQueries()*/



