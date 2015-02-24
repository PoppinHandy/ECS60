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
	  int p1Index = hashTable.insert(p1);
	  int p2Index = hashTable.insert(p2);
	  if (families[i].childCount > 0){
	    for(int j = 0; j < families[i].childCount; j++)
	      {
		child = Person2(families[i].children[j]);
		child.parent1 = p1Index;
		child.parent2 = p2Index;
		hashTable.insert(child); 
	      }//end inner for
	  }
	}//end outer if
      /*else 
	{
	  p1 = Person2(families[i].person);
	  hashTable.insert(p1);
	  }*/
    }//end outer for
  hashTable.displayHashTable(2480, 2530);
} // FamilyTree()

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
  Queue <Person2> q1(100000);
  Queue <Person2> q2(100000);
  Queue <Person2> q3(100000);
  Person2 ppl;
  int qCurrentLevel = 1;
  int qNextLevel = 0;
  
  //inserting first query into queue
  ppl = Person2(queries[0].person1);
  ppl = hashTable.findIndex(hashTable.insert(ppl));
  q1.enqueue(ppl);
  //cout << "ppl's id is: " << ppl.parent1 << endl;
  while (!q1.isEmpty())
    {
      Person2 currentNode = q1.getFront();
      cout << "inserting " << currentNode.person.firstName << endl;
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode.person.year != -1 && currentNode.parent1 > 0 && currentNode.parent2 > 0)
	{
	  q1.enqueue(hashTable.findIndex(ppl.parent1));
	  //cout << "inserting " << ppl.parent1 << endl;
	  q1.enqueue(hashTable.findIndex(ppl.parent2));
	  //cout << "inserting " << ppl.parent2 << endl;
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
      q2.enqueue(hashTable.findIndex(hashTable.insert(ppl)));
    }//end while
  q1.makeEmpty();
    
  qCurrentLevel = 1;
  qNextLevel = 0;
  
  //inserting second person into queue
  ppl = Person2(queries[0].person2);
  ppl = hashTable.findIndex(hashTable.insert(ppl));
  q1.enqueue(ppl);
  //cout << "ppl's id is: " << ppl.parent1 << endl;
  while (!q1.isEmpty())
    {
      Person2 currentNode = q1.getFront();
      cout << "inserting " << currentNode.person.firstName << endl;
      q1.dequeue();
      qCurrentLevel --;
      if(currentNode.person.year != -1 && currentNode.parent1 > 0 && currentNode.parent2 > 0)
	{
	  q1.enqueue(hashTable.findIndex(ppl.parent1));
	  //cout << "inserting " << ppl.parent1 << endl;
	  q1.enqueue(hashTable.findIndex(ppl.parent2));
	  //cout << "inserting " << ppl.parent2 << endl;
	  qNextLevel += 2;
	}//end if
      if(qCurrentLevel == 0)
	{
	  qCurrentLevel = qNextLevel;
	  qNextLevel = 0;
	}//end if
      q3.enqueue(hashTable.findIndex(hashTable.insert(ppl)));
    }//end while
  q1.makeEmpty();
  
} // runQueries()



