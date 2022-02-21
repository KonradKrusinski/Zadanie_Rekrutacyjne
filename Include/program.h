#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <iostream>
#include <filesystem>
#include <chrono>
#include "directory_traverser.h"
#include "threads_pool.h"
#include "file.h"

using std::cout,std::cin,std::endl,std::chrono::duration,std::chrono::milliseconds,std::chrono::high_resolution_clock;

class Program{
    int threadsNumber=0;
    string path;
    ThreadsPool *threadsPool;
    ResultContainer *resultContainer;
    duration<double> timeOneThread,timeFourThreads,timeUserThreads;


    //human communication methods
    int askForThreadsNumber();
    string askForPath();
    void printResults();

    void startThreadsPool();
    void traverseDirectories();
    void stopThreadsPool();
    void benchmarkThreads();

public:
    ~Program();
    void runProgram();
    void runProgramWithParameters(int, string, ResultContainer *);
};

#endif