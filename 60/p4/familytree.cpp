// Author: Sean Davis

#include "familytree.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

FamilyTree::FamilyTree(Family *families, int familyCount):hashTable(Person2(), familyCount*2)
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
            //cout << "Inserting: " << p1.person.firstName << " " << p1.id << endl;
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
    //hashTable.displayHashTable(100, 10000);
} // FamilyTree()

int compare (const void * a, const void * b)
{
    Person2 *ptr1 = (Person2*)a;
    Person2 *ptr2 = (Person2*)b;

    int retval = ptr2 -> person.year - ptr1-> person.year;
    if (retval != 0)
    {
        //cout << "here year" << endl;
        return retval;
    }
    retval = strncmp(ptr1 -> person.lastName, ptr2 -> person.lastName, 12);
    if (retval != 0)
    {
        //cout << "here last Name" << endl;
        return retval;
    }
    retval = strncmp(ptr1 -> person.firstName, ptr2 -> person.firstName, 12);
    if (retval != 0)
    {
        //cout << "here first Name" << endl;
        return retval;
    }
    return retval;
}//end compare

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{
    PersonQueue q1;
    PersonQueue q2;
    Person2 ppl;
    int qIndex, qSize;
    int q1_size;
    int q2_size;
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
        /*for (int i = 0; i < q1_size; i++)
          {
          cout <<  "Queue1: " << q1.theArray[i].person.firstName << " " << q1.theArray[i].person.lastName << ", " << q1.theArray[i].person.year << endl;
          }*/

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
                qIndex++;
            }
            q2_size ++;
        }//end while
        /*for (int i = 0; i < q2_size; i++)
          {
          cout <<  "Queue2: " << q2.theArray[i].person.firstName << " " << q2.theArray[i].person.lastName << ", " << q2.theArray[i].person.year << endl;
          }*/
        //Get common ancestor time


        qsort(&(q1.theArray[0]), q1_size - 1 , sizeof(Person2), compare);
        qsort(&(q2.theArray[0]), q2_size - 1 , sizeof(Person2), compare);
        memcpy(&answers[qc], &getAncestor(q1, q1_size, q2, q2_size), sizeof(Person));
        q1.theArray[q1_size].person.year = -1;
        q2.theArray[q2_size].person.year = -1;

    }//end Query loop
} // runQueries()


Person2& FamilyTree::getAncestor (PersonQueue &a, int a_size, PersonQueue &b, int b_size)
{
    /*for (int c = 0; c < a_size + 1; c++)
      {
      cout << "BEFORE SORT: " <<  a.theArray[c].person.year << ", " << "QueueA: " << a.theArray[c].person.firstName << endl;
      }

      for (int c = 0; c < b_size + 1; c++)
      {
      cout << "BEFORE SORT: " << b.theArray[c].person.year << ", " << "QueueB: " << b.theArray[c].person.firstName << endl;
      }*/
    /*for (int c = 0; c < a_size; c++)
      {
      cout << a.theArray[c].person.year << ", " << "QueueA: " << a.theArray[c].person.firstName << endl;
      }

      for (int c = 0; c < b_size; c++)
      {
      cout << b.theArray[c].person.year << ", " << "QueueB: " << b.theArray[c].person.firstName << endl;
      }*/
    //Person2 nullp = Person2();
    /*if (a_size < b_size)
      {
      for (int count = 0; count < a_size; count ++)
      {
      if(a.theArray[count].person.year < b.theArray[count].person.year)
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
      for (int count = 0; count < b_size; count ++)
      {
      if((a.theArray[count].person.year == b.theArray[count].person.year) && (a.theArray[count].id == b.theArray[count].id))
      {
      cout << "returned " << b.theArray[count].person.firstName << endl;
      return b.theArray[count];
      }
      }
      }*/
    int slowCount = 0;
    int fastCount = 0;
    while (slowCount < a_size && fastCount < b_size)
    {
        if (a.theArray[slowCount].person.year > b.theArray[fastCount].person.year)
        {
            slowCount++;
        }
        else
            if(a.theArray[slowCount].person.year < b.theArray[fastCount].person.year)
                fastCount++;
            else  
                if(strncmp (a.theArray[slowCount].person.lastName, b.theArray[fastCount].person.lastName, 12) < 0)
                    slowCount++;
                else
                    if(strncmp (a.theArray[slowCount].person.lastName, b.theArray[fastCount].person.lastName, 12) > 0)
                        fastCount++;
                    else
                        if (strncmp (a.theArray[slowCount].person.firstName, b.theArray[fastCount].person.firstName, 12) < 0)
                            slowCount++;
                        else
                            if (strncmp (a.theArray[slowCount].person.firstName, b.theArray[fastCount].person.firstName, 12) > 0)
                                fastCount++;
                            else
                                return a.theArray[slowCount];
    }
    b.theArray[20].person.year = -1;
    return b.theArray[20];
}//end getAncestor

void FamilyTree:: convertPerson2( Person2 &x, Person &y)
{
    strncpy( y.firstName, x.person.firstName, sizeof(x.person.firstName));
    //cout << "Copied " << y.firstName << " from " << x.person.firstName << endl;
    strcpy( y.lastName, x.person.lastName);
    //cout << "Copied " << y.lastName << " from " << x.person.lastName << endl;
    y.gender = x.person.gender;
    //cout << "Copied " << y.gender << " from " << x.person.gender << endl;
    y.year = x.person.year;
    //cout << "Copied " << y.year << " from " << x.person.year <<  endl;
    x.person.year = -1;
}
