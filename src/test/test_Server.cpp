#include <iostream>
#include "gtest/gtest.h"

#include "server/Server.h"

TEST(TestFunction, ReturnsXPlusOne)
{
    int result = Server::TestFunction(7);
    EXPECT_EQ(8, result);
}

TEST(TestFunction, FailsWhenResultNE)
{
    int result = Server::TestFunction(8);
    EXPECT_NE(8, result);
}

TEST(ProcessBuffer, ReturnsMinusOneIfError)
{
    char testBuffer[50];
    Server server;
    int result = server.ProcessBuffer(testBuffer);
    EXPECT_EQ(result, -1);
}

TEST(ProcessBuffer, ResultNEZero)
{
    char testBuffer[50];
    Server server;
    int result = server.ProcessBuffer(testBuffer);
    EXPECT_NE(result, 0);
}
