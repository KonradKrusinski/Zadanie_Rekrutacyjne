#include <iostream>
#include <fstream>
#include <string> 
#include <filesystem>
#include "gtest\gtest.h"
#include "file.h"

class FileTest : public ::testing::Test{
    protected:
    std::string createTestFile(){
        std::string path(std::filesystem::temp_directory_path().string());
        std::ofstream file;
        file.open(path+"test.txt", std::ofstream::out);
        file<<"First line in file"<<std::endl;
        file<<std::endl;
        file<<"Third line in file";
        file.close();
        return path+"test.txt";
    }
};

TEST_F(FileTest, CountFilesTest){
    ResultContainer container;
    File file(createTestFile(),&container);
    file.run();
    ASSERT_EQ(container.getFiles(),1);
}

TEST_F(FileTest, CountWordsTest){
    ResultContainer container;
    File file(createTestFile(),&container);
    file.run();
    ASSERT_EQ(container.getWords(),8);
}

TEST_F(FileTest, CountEmptyLinesTest){
    ResultContainer container;
    File file(createTestFile(),&container);
    file.run();
    ASSERT_EQ(container.getEmptyLines(),1);
}

TEST_F(FileTest, CountNonEmptyLinesTest){
    ResultContainer container;
    File file(createTestFile(),&container);
    file.run();
    ASSERT_EQ(container.getNonEmptyLines(),2);
}

TEST_F(FileTest, CountLettersTest){
    ResultContainer container;
    File file(createTestFile(),&container);
    file.run();
    ASSERT_EQ(container.getLetters(),30);
}