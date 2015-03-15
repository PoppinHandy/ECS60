#include "scheduler.h"
#include "VertexQueue.h"
#include <stdio.h>
#include "string.h"
#include <iostream>				
using namespace std;

Vertex::Vertex()
{
  indegree = 0;
  earliest = 0;
  latest = 0;
  topNum = 0;
  slack = 0;
}

Scheduler::Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople)
{
  array = new Vertex [numJobs];
  int indegs[100] = {0};
  VertexQueue queue;
  VertexQueue sorted;
  VertexQueue test;
  int previous = 0;
  for (int j = 0; j < numJobs; j++)
  {
    memcpy (&array[j].jb, &jobs[j], sizeof(Job));
    array[j].id = j;
    for (int i = 0; i < jobs[j].numDependencies; i++)
    {
      previous = jobs[j].dependencies[i];
      array[previous].prev[array[previous].indegree] = j;
      array[previous].indegree++;
      indegs[previous]++;
    }//inner for
  }//outer for
  //============================For Debugging==========================
  /*for (int c = 0; c < numJobs; c++)
    {
    cout << "Job ID: " << array[c].id << endl;
    cout << "Previous: ";
    for (int a = 0; a < array[c].indegree; a++)
    {
    cout << array[c].prev[a] << " ";
    }
    cout << endl;
    cout << "Next: ";
    for (int b = 0; b < array[c].jb.numDependencies; b++)
    {
    cout << array[c].jb.dependencies[b] << " ";
    }
    cout << endl;
    cout << "Weight: " << array[c].jb.length << endl;
    cout << "Indegree: " << array[c].indegree << endl;
    cout << "Outdegree: " << array[c].jb.numDependencies << endl;
    cout << endl;
    }*/
  //=====================================================================

  //=========Top Sort begins here===============
  int counter = 0;
  for (int jc = 0; jc < numJobs; jc++)
  {
    if (indegs[jc] == 0)
    {
      queue.enqueue(array[jc]);
    }
    /*while (!queue.isEmpty())
      {
      Vertex v = queue.dequeue();
    //v.topNum = counter++;
    sorted.enqueue(v);
    //if adjacent vertexes, then decrement indegree and see which = 0
    for (int adj = 0; adj < v.jb.numDependencies; adj++)
    {
    int nextNum = v.jb.dependencies[adj];
    if(--indegs[nextNum] == 0)
    {
    queue.enqueue(array[nextNum]);
    }
    } //end inner for
    }//end while*/
  }//end outer for
  while (!queue.isEmpty())
  {
    Vertex v = queue.dequeue();
    v.topNum = counter++;
    sorted.enqueue(v);
    //if adjacent vertexes, then decrement indegree and see which = 0
    for (int adj = 0; adj < v.jb.numDependencies; adj++)
    {
      int nextNum = v.jb.dependencies[adj];
      if(--indegs[nextNum] == 0)
      {
        queue.enqueue(array[nextNum]);
      }
    } //end inner for
  }//end while
  //==========================Top sort Debug==============
  /*for (int q = 0 ; q < numJobs; q++)
    {
    cout << sorted.theArray[q].id << " ";
    }
    cout << endl;
    for (int l = 0 ; l < numJobs; l++)
    {
    cout << sorted.theArray[l].topNum << " ";
    }
    cout << endl;*/
  //=======================================================

  //Calculating critical path
  int lastPos = 0;
  //Looking for earliest time
  for (int s = 0; s < numJobs; s++)
  {
    if (sorted.theArray[s].indegree == 0)
    {
      sorted.theArray[s].earliest = sorted.theArray[s].jb.length;
    }
    else if (sorted.theArray[s].indegree > 0)
    {
      for (int pNum = 0; pNum < sorted.theArray[s].indegree; pNum++)
      {
        for (int m = lastPos; m < s; m++)
        {
          if(sorted.theArray[m].id == sorted.theArray[s].prev[pNum])
          {
            if (sorted.theArray[s].earliest < sorted.theArray[m].earliest)
            {
              sorted.theArray[s].earliest = sorted.theArray[m].earliest;
            }
          }
        }
      }
      sorted.theArray[s].earliest += sorted.theArray[s].jb.length;
    }//end else if
    //cout << "Job ID: " << sorted.theArray[s].id << endl;
    //cout << "Earliest Time: " << sorted.theArray[s].earliest << endl;
  }//end outer for

  //looking for latest time
  for (int d = numJobs - 1; d >= 0; d--)
  {
    if (sorted.theArray[d].jb.numDependencies == 0)
    {
      heap.insert(sorted.theArray[d].earliest);
      sorted.theArray[d].latest = heap.findMax();
      sorted.theArray[d].slack = sorted.theArray[d].latest - sorted.theArray[d].earliest;
    }
    else if (sorted.theArray[d].jb.numDependencies > 0)
    {
      sorted.theArray[d].latest = 1000;
      for (int dependent = 0; dependent < sorted.theArray[d].jb.numDependencies; dependent++)
      {
        for (int b = numJobs - 1; b > d; b--)
        {
          if(sorted.theArray[b].id == sorted.theArray[d].jb.dependencies[dependent])
          {
            if (sorted.theArray[d].latest > (sorted.theArray[b].latest - sorted.theArray[b].jb.length))
            {
              sorted.theArray[d].latest = sorted.theArray[b].latest - sorted.theArray[b].jb.length;
              sorted.theArray[d].slack = sorted.theArray[d].latest - sorted.theArray[d].earliest;
            }
          }
        }
      }
    }//end else if
    //cout << "Job ID: " << sorted.theArray[d].id << endl;
    //cout << "Latest Time: " << sorted.theArray[d].latest << endl;
  }//end outer for
//for (int i = 0 ; i < numJobs; ++i) {
  //cout << sorted.theArray[i].id << endl;
//}
  while (!sorted.isEmpty()) {
    for (int i = 0; i < numJobs; ++i) {
      if (sorted.theArray[i].indegree == 0) {
        jobs[sorted.theArray[i].id].startTime = 0;
        for (int k = 0; k < numWorkers; ++k) {
          jobs[sorted.theArray[i].id].peopleIDs[k] = k+1;
          jobs[sorted.theArray[i].id].numPeopleUsed++;
        }
        sorted.dequeue();
      }
      else {
        for (int j = 0; j < numWorkers; ++j) {
          jobs[sorted.theArray[i].id].startTime = sorted.theArray[i].earliest;
          if ( sorted.theArray[i].slack==0 && j != numWorkers -1 )
          {
            jobs[sorted.theArray[i].id].peopleIDs[j] = j+1;
            jobs[sorted.theArray[i].id].numPeopleUsed++;
          }
          else {
            jobs[sorted.theArray[i].id].peopleIDs[j] = j+1;
            jobs[sorted.theArray[i].id].numPeopleUsed++;
          }
        } // Scheduler()
        sorted.dequeue();
      }
    }
  }
}

void Scheduler::run()
{
} // run()


