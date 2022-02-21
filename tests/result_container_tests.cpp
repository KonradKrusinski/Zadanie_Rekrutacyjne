#include "gtest\gtest.h"
#include "result_container.h"

class ResultContainerTest : public ::testing::Test{
    protected:
    void fillDataIntoContainer(ResultContainer *container){
        container -> addData(10,8,4,22);
    }
};


TEST_F(ResultContainerTest, FilesCounterTest) {
    ResultContainer container;
    fillDataIntoContainer(&container);
    ASSERT_EQ(container.getFiles(),1);
}

TEST_F(ResultContainerTest, WordsCounterTest) {
    ResultContainer container;
    fillDataIntoContainer(&container);
    ASSERT_EQ(container.getWords(),10);
}

TEST_F(ResultContainerTest, EmptyLinesCounterTest) {
    ResultContainer container;
    fillDataIntoContainer(&container);
    ASSERT_EQ(container.getEmptyLines(),8);
}

TEST_F(ResultContainerTest, NonEmptyLinesCounterTest) {
    ResultContainer container;
    fillDataIntoContainer(&container);
    ASSERT_EQ(container.getNonEmptyLines(),4);
}

TEST_F(ResultContainerTest, LettersCounterTest) {
    ResultContainer container;
    fillDataIntoContainer(&container);
    ASSERT_EQ(container.getLetters(),22);
}

TEST_F(ResultContainerTest, FoldersCounterTest) {
    ResultContainer container;
    container.folderFound();
    ASSERT_EQ(container.getFolders(),1);
}