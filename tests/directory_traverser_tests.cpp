#include <iostream>
#include <fstream>
#include <string> 
#include <filesystem>
#include <ctime>
#include <sstream>
#include "gtest\gtest.h"
#include "directory_traverser.h"
#include "threads_pool.h"
namespace fs = std::filesystem;

TEST(DirectoryTraverserTest, FoundFoldersCountTest){
    ResultContainer container;
    std::string path ="";
    DirectoryTraverser traverser(path,NULL,&container);
    ASSERT_EQ(container.getFolders(),1);
}

TEST (DirectoryTraverserTest, QueingJobsForFoldersTest){
    ResultContainer container;
    fs::current_path(fs::temp_directory_path());
    std::stringstream stream;
    stream << std::time(0);
    string folderPath(stream.str());
    folderPath = "TestFolder"+folderPath;
    fs::create_directory(folderPath);
    fs::create_directory(folderPath+"/TestFolder1");
    fs::create_directory(folderPath+"/TestFolder2");
    std::string path(std::filesystem::temp_directory_path().string()+folderPath);
    ThreadsPool pool;
    pool.enqueueJob(new DirectoryTraverser(path,&pool,&container));
    while(!pool.jobsDone()){}
    ASSERT_EQ(pool.getNumberOfJobsEnqueued(),3);
}

TEST (DirectoryTraverserTest, QueingJobsForFilesTest){
    ResultContainer container;
    fs::current_path(fs::temp_directory_path());
    std::stringstream stream;
    stream << std::time(0);
    string folderPath(stream.str());
    folderPath = "TestFolderFiles" + folderPath;
    fs::create_directory(folderPath);
    std::string path(std::filesystem::temp_directory_path().string()+folderPath);
    std::ofstream file;
    file.open(path+"/test.txt", std::ofstream::out);
    file<<"First line in file"<<std::endl;
    file<<std::endl;
    file<<"Third line in file";
    file.close();
    file.open(path+"/test2.txt", std::ofstream::out);
    file<<"First line in file"<<std::endl;
    file<<std::endl;
    file<<"Third line in file";
    file.close();
    ThreadsPool pool;
    pool.enqueueJob(new DirectoryTraverser(path,&pool,&container));
    while(!pool.jobsDone()){}
    ASSERT_EQ(pool.getNumberOfJobsEnqueued(),3);
}