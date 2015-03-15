#ifndef schedulerH
#define schedulerH
#include "ProjectRunner.h"
#include "BinaryHeap.h"
class Vertex
{
 public:
  Vertex();
  Job jb;
  int earliest;
  int latest;
  int id;
  int prev [100];
  int indegree;
  int topNum;
  int slack;
}; //class vertex

class Scheduler
{
public:
  Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople);
  void run();
  Vertex *array;
  BinaryHeap <int> heap;
}; // class Scheduler

#endif
