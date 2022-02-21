#ifndef THREADS_POOL_H
#define THREADS_POOL_H

#include <thread>
#include <vector>
#include <mutex>
#include "job.h"

using std::vector,std::mutex,std::condition_variable,std::thread,std::unique_lock,std::lock_guard;

class ThreadsPool{
    vector<thread> threads;
    int totalJobsEnqueued=0;
    mutex jobsVectorMutex;
    vector<Job *> jobs;
    bool threadsStopped=true;
    bool terminatePool=false;
    condition_variable conditionVariable;
    
    //things needed for monitoring how many threads are busy
    int busyThreads=0;
    mutex busyThreadsMutex;
    bool areThreadsBusy();
    void changeBusyThreadsCounter(bool);

public:
    ThreadsPool(int = 1);
    ~ThreadsPool();
    void enqueueJob(Job *);
    void stopThreads();
    void workerLoop();
    bool jobsDone();
    int getNumberOfThreads();
    int getNumberOfJobsEnqueued();
};

#endif