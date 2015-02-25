// Author: Sean Davis

#include "familytree.h"
#include <stdlib.h>
#include <string.h>

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
  hashTable.displayHashTable(100, 5000);
} // FamilyTree()

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
  Queue <Person2> q1(10);
  Queue <Person2> q2(10);
  Person2 ppl;
  int q1_size = 1;
  int q2_size = 1;
  int answerCount = 0;
  int qCurrentLevel = 1;
  int qNextLevel = 0;
  for (int qc = 0; qc < queryCount; qc++){
    q1.makeEmpty();
    q2.makeEmpty();
    q1_size = 1;
    q2_size = 1;
    //inserting first query into queue
    ppl = Person2(queries[qc].person1);
    ppl = hashTable.findIndex(hashTable.insert(ppl));
    q1.enqueue(ppl);
    //cout << "ppl's id is: " << ppl.parent1 << endl;
    // Start level-order traversal
    while (!q1.isEmpty())
      {
	Person2 currentNode = q1.getFront();
	//cout << "inserting " << currentNode.person.firstName << endl;
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
	q1_size ++;
      }//end while
    for (int i = 0; i < q1_size - 1; i++){
      cout <<  "Queue1: " << q1.theArray[i].person.firstName << " " << q1.theArray[i].person.lastName << endl;
    }
    
    //Reset vars for next person
    qCurrentLevel = 1;
    qNextLevel = 0;
  
    //inserting second person into queue
    ppl = Person2(queries[qc].person2);
    ppl = hashTable.findIndex(hashTable.insert(ppl));
    q2.enqueue(ppl);
    //cout << "ppl's id is: " << ppl.parent1 << endl;
    // Start level-order traversal
    while (!q2.isEmpty())
      {
	Person2 currentNode = q2.getFront();
	//cout << "inserting " << currentNode.person.firstName << endl;
	q2.dequeue();
	qCurrentLevel --;
	if(currentNode.person.year != -1 && currentNode.parent1 > 0 && currentNode.parent2 > 0)
	  {
	    q2.enqueue(hashTable.findIndex(ppl.parent1));
	    //cout << "inserting " << ppl.parent1 << endl;
	    q2.enqueue(hashTable.findIndex(ppl.parent2));
	    //cout << "inserting " << ppl.parent2 << endl;
	    qNextLevel += 2;
	  }//end if
	if(qCurrentLevel == 0)
	  {
	    qCurrentLevel = qNextLevel;
	    qNextLevel = 0;
	  }//end if
	q2_size ++;
      }//end while
    for (int i = 0; i < q2_size - 1; i++)
      {
	cout <<  "Queue2: " << q2.theArray[i].person.firstName << " " << q2.theArray[i].person.lastName << endl;
      }
    
    //Get common ancestor time
    convertPerson2(getAncestor(q1, q1_size, q2, q2_size), answers[answerCount]);
  }//end Query loop
} // runQueries()

int compare (const void * a, const void * b)
{
  if ( (*(Person2*)a).person.year < (*(Person2*)b).person.year )
    return 1;
  if ( (*(Person2*)a).person.year == (*(Person2*)b).person.year )
    {
      if(strcmp ((*(Person2*)a).person.lastName,(*(Person2*)b).person.lastName) == 0)
	{
	  return strcmp ((*(Person2*)a).person.firstName,(*(Person2*)b).person.firstName);
	}
      else
	{
	  return strcmp ((*(Person2*)a).person.lastName,(*(Person2*)b).person.lastName);
	}
    }
  if ( (*(Person2*)a).person.year > (*(Person2*)b).person.year )
    return -1;
  return 0;
}//end compare

Person2& FamilyTree::getAncestor (Queue <Person2> &a, int a_size, Queue <Person2> &b, int b_size)
{
  qsort(&a.theArray, sizeof(a)/sizeof(Person2) , sizeof(Person2), compare);
  qsort(&b.theArray, sizeof(b)/sizeof(Person2) , sizeof(Person2), compare);
  Person2 nullp = Person2();
  if (a_size < b_size)
    {
      for (int count = 0; count < a_size - 1; count ++)
	{
	  if((a.theArray[count].person.year == b.theArray[count].person.year)) && (a.theArray[count].id == b.theArray[count].id))
	    {
	      return a.theArray[count];
	    }
	}
    }
  else
    {
       for (int count = 0; count < b_size - 1; count ++)
	 {
	  if((a.theArray[count].person.year == b.theArray[count].person.year) && (a.theArray[count].id == b.theArray[count].id))
	    {
	      cout << "returned " << b.theArray[count].person.firstName << endl;
	      return b.theArray[count];
	    }
	}
    }
  return nullp;
}//end getAncestor

void FamilyTree:: convertPerson2( Person2 &x, Person &y)
{
  strcpy( y.firstName, x.person.firstName);
  strcpy( y.lastName, x.person.lastName);
  y.gender = x.person.gender;
  y.year = x.person.year;
  
}
