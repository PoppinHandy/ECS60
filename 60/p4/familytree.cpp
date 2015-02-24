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
      if (families[i].spouse.year != -1 && families[i].person.year != -1)
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
	}
      else 
	{
	  p1 = Person2(families[i].person);
	  hashTable.insert(p1);
	}
    }//end outer for
} // FamilyTree()

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
  Queue <int> q1(100000);
  Queue <Person2> q2(100000);
  Queue <Person2> q3(100000);
  int qCurrentLevel = 1;
  int qNextLevel = 0;
  
  //inserting first query into queue
  Person2 ppl;
  ppl = Person2(queries[0].person1);
  ppl = hashTable.findIndex(hashTable.insert(ppl));
  q1.enqueue(hashTable.insert(ppl));
  cout << q1.getFront() << endl;
  while (!q1.isEmpty())
    {
      int currentNode = q1.getFront();
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode != 0 && ppl.parent1 != 0 && ppl.parent2 != 0)
	{
	  ppl = hashTable.findIndex(ppl.parent1);
	  q1.enqueue(hashTable.insert(ppl));
	  ppl = hashTable.findIndex(ppl.parent2);
	  q1.enqueue(hashTable.insert(ppl));
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
      q2.enqueue(hashTable.findIndex(currentNode));
      cout << q2.getFront().person.firstName << endl;
  }//end while
  q1.makeEmpty();

  //inserting second query into queue
  ppl = Person2(queries[0].person2);
  ppl = hashTable.findIndex(hashTable.insert(ppl));
  q1.enqueue(hashTable.insert(ppl));
  cout << q1.getFront() << endl;
  while (!q1.isEmpty())
    {
      int currentNode = q1.getFront();
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode != 0 && ppl.parent1 != 0 && ppl.parent2 != 0)
	{
	  ppl = hashTable.findIndex(ppl.parent1);
	  q1.enqueue(hashTable.insert(ppl));
	  ppl = hashTable.findIndex(ppl.parent2);
	  q1.enqueue(hashTable.insert(ppl));
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
      q3.enqueue(hashTable.findIndex(currentNode));
      cout << q3.getFront().person.firstName << endl;
  }//end while
  q1.makeEmpty();
} // runQueries()



