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
	  cout << "Inserting: " << p1.person.firstName << " " << p1.id << endl;
	  int p1Index = hashTable.insert(p1);
	  int p2Index = hashTable.insert(p2);
	  if (families[i].childCount > 0)
	    {
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
  Queue <Person2> q1(30);
  Queue <Person2> q2(30);
  Person2 ppl;
  int qIndex, qSize;
  int q1_size;
  int q2_size = 1;
  //int qNextLevel = 0;
  //int qCurrentLevel = 1;
  for (int qc = 0; qc < queryCount; qc++){
    qSize = 1;
    qIndex = 0;
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
    while (qIndex != qSize)
      {
	Person2 currentNode = q1.theArray[qIndex];
	//cout << "inserting " << currentNode.person.firstName << endl;
	if(currentNode.person.year != -1 && currentNode.parent1 > 0 && currentNode.parent2 > 0)
	  {
	    q1.enqueue(hashTable.findIndex(currentNode.parent1));
	    //cout << "inserting " << ppl.parent1 << endl;
	    q1.enqueue(hashTable.findIndex(currentNode.parent2));
	    //cout << "inserting " << ppl.parent2 << endl;
	    qSize += 2;
	    qIndex ++;
	  }//end if
	else
	  {
	    qIndex ++;
	  }
	q1_size ++;
      }//end while
    for (int i = 0; i < q1_size - 1; i++)
      {
	cout <<  "Queue1: " << q1.theArray[i].person.firstName << " " << q1.theArray[i].person.lastName << endl;
      }
    
    //Reset vars for next person
    qSize = 1;
    qIndex = 0;
  
    //inserting second person into queue
    ppl = Person2(queries[qc].person2);
    ppl = hashTable.findIndex(hashTable.insert(ppl));
    q2.enqueue(ppl);
    //cout << "ppl's id is: " << ppl.parent1 << endl;
    // Start level-order traversal
    while (qIndex != qSize)
      {
	Person2 currentNode = q2.theArray[qIndex];
	//cout << "inserting " << currentNode.person.firstName << endl;
	if(currentNode.person.year != -1 && currentNode.parent1 > 0 && currentNode.parent2 > 0)
	  {
	    q2.enqueue(hashTable.findIndex(currentNode.parent1));
	    //cout << "inserting " << ppl.parent1 << endl;
	    q2.enqueue(hashTable.findIndex(currentNode.parent2));
	    //cout << "inserting " << ppl.parent2 << endl;
	    qSize += 2;
	    qIndex ++;
	  }//end if
	else
	  {
	    qIndex ++;
	  }//end if
	q2_size ++;
      }//end while
    for (int i = 0; i < q2_size - 1; i++)
      {
	cout <<  "Queue2: " << q2.theArray[i].person.firstName << " " << q2.theArray[i].person.lastName << endl;
      }
      //Get common ancestor time

    /*q1.makeEmpty();
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
	    q1.enqueue(hashTable.findIndex(currentNode.parent1));
	    //cout << "inserting " << ppl.parent1 << endl;
	    q1.enqueue(hashTable.findIndex(currentNode.parent2));
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
      cout << "Queue1: " << q1.theArray[i].person.firstName << " " << q1.theArray[i].person.lastName << endl;
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
	    q2.enqueue(hashTable.findIndex(currentNode.parent1));
	    //cout << "inserting " << ppl.parent1 << endl;
	    q2.enqueue(hashTable.findIndex(currentNode.parent2));
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
	cout << "Queue2: " << q2.theArray[i].person.firstName << " " << q2.theArray[i].person.lastName << endl;
      }
      //Get common ancestor time*/


    convertPerson2(getAncestor(q1, q1_size, q2, q2_size), answers[qc]);
  }//end Query loop
} // runQueries()

int compare (const void * a, const void * b)
{
  /*if ( (*(Person2*)a).person.year < (*(Person2*)b).person.year )
    cout << "moved ayear < byear" << endl;
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
    cout << "moved ayear < byear" << endl;
    return -1;
  return 0;*/
  Person2 *ptr1 = (Person2*)a;
  Person2 *ptr2 = (Person2*)b;
  
  int retval = ptr2 -> person.year - ptr1-> person.year;
  if (retval != 0)
    {
      cout << "here year" << endl;
      return retval;
    }
  retval = strncmp(ptr1 -> person.lastName, ptr2 -> person.lastName, 12);
   if (retval != 0)
    {
         cout << "here last Name" << endl;
      return retval;
    }
   retval = strncmp(ptr1 -> person.firstName, ptr2 -> person.firstName, 12);
   if (retval != 0)
    {
      cout << "here first Name" << endl;
      return retval;
    }
   return retval;
}//end compare

Person2& FamilyTree::getAncestor (Queue <Person2> &a, int a_size, Queue <Person2> &b, int b_size)
{
  qsort(&(a.theArray[0]), a_size , sizeof(Person2), compare);
  qsort(&(b.theArray[0]), b_size , sizeof(Person2), compare);
  for (int c = 0; c < a_size - 1; c++)
    {
      cout << a.theArray[c].person.year << ", " << "QueueA: " << a.theArray[c].person.firstName << endl;
    }

  for (int c = 0; c < b_size - 1; c++)
    {
       cout << b.theArray[c].person.year << ", " << "QueueB: " << b.theArray[c].person.firstName << endl;
    }
  //Person2 nullp = Person2();
  if (a_size < b_size)
    {
      for (int count = 0; count < a_size - 1; count ++)
	{
	  if((a.theArray[count].person.year == b.theArray[count].person.year) && (a.theArray[count].id == b.theArray[count].id))
	    {
	      cout << "returned " << a.theArray[count].person.firstName << endl;
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
  
  return b.theArray[20];
}//end getAncestor

void FamilyTree:: convertPerson2( Person2 &x, Person &y)
{
  strncpy( y.firstName, x.person.firstName, sizeof(x.person.firstName));
  cout << "Copied " << y.firstName << " from " << x.person.firstName << endl;
  strcpy( y.lastName, x.person.lastName);
  cout << "Copied " << y.lastName << " from " << x.person.lastName << endl;
  y.gender = x.person.gender;
  cout << "Copied " << y.gender << " from " << x.person.gender << endl;
  y.year = x.person.year;
  cout << "Copied " << y.year << " from " << x.person.year <<  endl;
  
}
