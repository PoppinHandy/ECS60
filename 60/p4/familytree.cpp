// Author: Sean Davis

#include "familytree.h"
#include "QueueAr.h"

using namespace std;

FamilyTree::FamilyTree(Family *families, int familyCount):hashTable(Person2(), 100000)
{
  Person2 child;
  Person2 p1;
  Person2 p2;
  for(int i = 0; i < familyCount; i++)
    {
      p1 = Person2(families[i].person);
      p2 = Person2(families[i].spouse);
      hashTable.insert(p1);
      hashTable.insert(p2);
      for(int j = 0; j < families[i].childCount; j++)
	{
	  child = Person2(families[i].children[j]);
	  hashTable.insert(child);
	  child.setParent(p1, p2);
	}//end inner for
    }//end outer for
} // FamilyTree()

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
  Queue <Person2> q1(100000);
  Queue <Person2> q2(100000);
  Queue <Person2> q3(100000);
  int qCurrentLevel = 1;
  int qNextLevel = 0;
  
  //inserting first query into queue
  q1.enqueue(Person2(queries[0].person1));
  while (!q1.isEmpty())
    {
      const Person2 currentNode = q1.getFront();
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode.person.year != -1)
	{
	  q1.enqueue(hashTable.findIndex(currentNode.parent1));
	  q1.enqueue(hashTable.findIndex(currentNode.parent2));
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
       q2.enqueue(currentNode);
  }//end while
  q1.makeEmpty();

  //inserting second query into queue
  q1.enqueue(Person2(queries[0].person2));
  while (!q1.isEmpty())
    {
      const Person2 currentNode = q1.getFront();
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode.person.year != -1)
	{
	  q1.enqueue(hashTable.findIndex(currentNode.parent1));
	  q1.enqueue(hashTable.findIndex(currentNode.parent2));
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
       q2.enqueue(currentNode);
  }//end while
} // runQueries()



