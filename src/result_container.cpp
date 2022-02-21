#include "result_container.h"

void ResultContainer::addData(int wordsToAdd,int emptyLinesToAdd,int nonEmptyLinesToAdd,int lettersToAdd){
    std::unique_lock<std::mutex> lock(mutexLock);
    files++;
    words += wordsToAdd;
    emptyLines += emptyLinesToAdd;
    nonEmptyLines += nonEmptyLinesToAdd;
    letters += lettersToAdd;
}

int ResultContainer::getWords(){
    return words;
}

int ResultContainer::getEmptyLines(){
    return emptyLines;
}

int ResultContainer::getNonEmptyLines(){
    return nonEmptyLines;
}

int ResultContainer::getLetters(){
    return letters;
}

int ResultContainer::getFiles(){
    return files;
}

int ResultContainer::getFolders(){
    return folders;
}

void ResultContainer::folderFound(){
    std::unique_lock<std::mutex> lock(mutexLock);
    folders++;
}