#include "scheduler.h"
#include "VertexQueue.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Vertex::Vertex()
{
  indegree = 0;
  weight = 0;
  outdegree = 0;
}

Scheduler::Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople)
{
  array = new Vertex [numJobs];
  VertexQueue queue;
  VertexQueue sorted;
  int previous = 0;
  for (int j = 0; j < numJobs; j++)
    {
      array[j].id = j;
      array[j].weight = jobs[j].length;
      array[j].outdegree = jobs[j].numDependencies;
      for (int i = 0; i < jobs[j].numDependencies; i++)
	{
	  array[j].next[i] = jobs[j].dependencies[i];
	  previous = jobs[j].dependencies[i];
	  array[previous].prev[array[previous].indegree] = j;
	  array[previous].indegree++;
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
      for (int b = 0; b < jobs[c].numDependencies; b++)
	{
	  cout << array[c].next[b] << " ";
	}
      cout << endl;
      cout << "Weight: " << array[c].weight << endl;
      cout << "Indegree: " << array[c].indegree << endl;
      cout << "Outdegree: " << array[c].outdegree << endl;
      cout << endl;
      }*/
  //=====================================================================

  //=========Top Sort begins here===============
  
  for (int jc = 0; jc < numJobs; jc++)
    {
      if (array[jc].indegree == 0)
	{
	  queue.enqueue(array[jc]);
	}
      while (!queue.isEmpty())
	{
	  Vertex v = queue.dequeue();
	  sorted.enqueue(v);
	  //if adjacent vertexes, then decrement indegree and see which = 0
	  for (int adj = 0; adj < v.outdegree; adj++)
	    {
	      int nextNum = v.next[adj];
	      if(--array[nextNum].indegree == 0)
		{
		  queue.enqueue(array[nextNum]);
		}
	    } //end inner for
	}//end while
    }//end outer for
  //==========================Top sort Debug==============
  /*for (int q = 0 ; q < numJobs; q++)
    {
      cout << sorted.theArray[q].id << " ";
    }
    cout << endl;*/
  //=======================================================
} // Scheduler()

void Scheduler::run()
{
} // run()


