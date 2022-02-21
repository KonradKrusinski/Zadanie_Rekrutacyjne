#include "gtest\gtest.h"
#include "threads_pool.h"

TEST(ThreadsPoolTest, IdleAtStartTest){
    ThreadsPool pool(2);
    ASSERT_TRUE(pool.jobsDone());
}

TEST(ThreadsPoolTest, CreatingCorrectNumberOfThreadsTest){
    ThreadsPool pool(2);
    ASSERT_EQ(pool.getNumberOfThreads(),2);
}