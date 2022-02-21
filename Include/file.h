#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "result_container.h"
#include "job.h"

using std::string,std::ifstream;

class File : public Job{
    string path;
    ResultContainer *resultContainer;
public:
    File(string,ResultContainer*);
    virtual void run();
};


#endif