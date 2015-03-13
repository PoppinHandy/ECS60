#include "scheduler.h"
#include "Queue.h"
#include <iostream>

using namespace std;

typedef struct node {
    int id;
    int weight;
    int outedges;
    int inedges;
    node* next;
    int neighbors[5000];
};

Scheduler::Scheduler(int numJobs, int numWorkers, Job *jobs, int numPeople)
{
    node *n;
    node *A[numJobs];
    Queue q;
    int sorted[50000];
    for (int i = 0; i < numJobs; ++i) {
        n->id = i;
        n->weight = jobs[i].length;
        if (jobs[i].numDependencies > 0) {
            for (int j = 0; j < jobs[i].numDependencies; ++j) {
                n->neighbors[j] = jobs[i].dependencies[j];
                ++n->outedges;
            }
        }
        A[i] = n;
        n->next = new node;
        n = n->next;
    }
    for (int i = 0; i < numJobs; ++i) {
        //cout << A[i]->id << " has " << A[i]->outedges << " outedges" << endl;
        if (A[i]->outedges > 0)
        {
            for (int j = 0; j < A[i]->outedges; ++j)
                for (int k = 0; k < numJobs; ++k)
                    if (A[i]->neighbors[j] == A[k]->id) 
                        ++A[k]->inedges;
        }
    }
    q.makeEmpty();
    //for (int i = 0; i < 100000; ++i) 
        //cout << q.theArray[i] << endl;
    for (int i = 0; i < numJobs; ++i) {
        if (A[i]->inedges == 0)
            q.enqueue(A[i]->id);
    }
    //while (!q.isEmpty()) {
        for (int i = 0; i < numJobs; ++i) {
            sorted[i] = q.dequeue();
            for (int j = 0; j < A[i]->outedges; ++j) {
                --A[A[i]->neighbors[j]]->inedges;
                q.enqueue(A[A[i]->neighbors[j]]->id);
            }
        }
    //}
    for (int i = 0; i < numJobs; ++i) 
        cout << sorted[i] << endl;
} // Scheduler()


void Scheduler::run()
{
} // run()
