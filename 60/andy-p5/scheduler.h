#ifndef schedulerH
#define schedulerH

#include "ProjectRunner.h"
class Vertex
{
 public:
  Vertex();
  int id;
  int weight;
  int prev [100];
  int next [100];
  int indegree;
  int outdegree;
}; //class vertex

class Scheduler
{
public:
  Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople);
  void run();
  Vertex *array;
}; // class Scheduler

#endif
