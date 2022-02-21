#include "directory_traverser.h"

DirectoryTraverser::DirectoryTraverser(string givenPath, ThreadsPool *givenThreadsPool, ResultContainer *givenResultContainer){
    pathString=givenPath;
    threadsPool = givenThreadsPool;
    resultContainer = givenResultContainer;
    resultContainer -> folderFound();
}

void DirectoryTraverser::run(){
    const std::filesystem::path path(pathString);

    for(auto const& dir_entry : std::filesystem::directory_iterator(path)){

        if(dir_entry.is_directory()){

            threadsPool -> enqueueJob( new DirectoryTraverser(dir_entry.path().string(), threadsPool, resultContainer));

        }else if(dir_entry.is_regular_file()){
            string fileName= dir_entry.path().string();
            string extension=".txt";
            if(fileName.compare( fileName.length() - extension.length(), extension.length() ,extension)==0){
                threadsPool -> enqueueJob( new File(dir_entry.path().string(), resultContainer));
            }
        }
    }
}