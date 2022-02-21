#ifndef DIRECTORY_TRAVERSER_H
#define DIRECTORY_TRAVERSER_H

#include <string>
#include <filesystem>
#include "threads_pool.h"
#include "result_container.h"
#include "file.h"

using std::string;

class DirectoryTraverser : public Job{
    string pathString;
    ThreadsPool *threadsPool;
    ResultContainer *resultContainer;
public:
    DirectoryTraverser(string,ThreadsPool *,ResultContainer *);
    virtual void run();
};

#endif