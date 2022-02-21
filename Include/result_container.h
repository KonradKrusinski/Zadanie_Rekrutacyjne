#ifndef RESULT_CONTAINER_H
#define RESULT_CONTAINER_H

#include <mutex>

class ResultContainer{
    int words=0;
    int emptyLines=0;
    int nonEmptyLines=0;
    int letters=0;
    int files=0;
    int folders=0;
    std::mutex mutexLock;
public:
    void addData(int,int,int,int);
    void folderFound();
    int getWords();
    int getEmptyLines();
    int getNonEmptyLines();
    int getLetters();
    int getFiles();
    int getFolders();
};

#endif