#include "threads_pool.h"


ThreadsPool::ThreadsPool(int threadsNumber){
    for(int i=0;i<threadsNumber;i++){
        threads.push_back(thread(&ThreadsPool::workerLoop,this));
    }
    threadsStopped=false;
}

ThreadsPool::~ThreadsPool(){

    if(!threadsStopped){
        stopThreads();
    }

    if(!jobs.empty()){
        for (Job *job : jobs){
            delete job;
        }
        jobs.clear();
    }

}

void ThreadsPool::stopThreads(){
    terminatePool = true; 
    conditionVariable.notify_all();
    for (std::thread &th : threads)
    {
        th.join();
    }
    jobs.clear();  
    threadsStopped = true; 
}

void ThreadsPool::workerLoop(){
    while (true){

        Job *job;
        bool gotJob=false;

        {
            unique_lock<mutex> lock(jobsVectorMutex);
            conditionVariable.wait( lock, [this](){
                return !jobs.empty() || terminatePool;
            });

            if(!jobs.empty()){
                changeBusyThreadsCounter(true);
                gotJob=true;
                job = jobs.front();
                jobs.erase(jobs.begin());
            }

        }

        if(gotJob){
            job -> run();
            delete job;
            changeBusyThreadsCounter(false);
        }

        if(terminatePool) {
            return;
        }
    }
}

void ThreadsPool::enqueueJob(Job *job){
    
    {
        lock_guard<mutex> lock(jobsVectorMutex);
        totalJobsEnqueued++;
        jobs.push_back(job);
    }

    conditionVariable.notify_one();
}

bool ThreadsPool::jobsDone(){
    bool jobsEmpty = false;

    {
        lock_guard<mutex> lock(jobsVectorMutex);
        jobsEmpty=jobs.empty();
    }

    return jobsEmpty&&!areThreadsBusy();
}

bool ThreadsPool::areThreadsBusy(){
    lock_guard<mutex> lock(busyThreadsMutex);
    return busyThreads>0;
}

void ThreadsPool::changeBusyThreadsCounter(bool increase){
    lock_guard<mutex> lock(busyThreadsMutex);
    if(increase){
        busyThreads++;
    }else{
        busyThreads--;
    }
}

int ThreadsPool::getNumberOfThreads(){
    return threads.size();
}

int ThreadsPool::getNumberOfJobsEnqueued(){
    lock_guard<mutex> lock(jobsVectorMutex);
    return totalJobsEnqueued;
}