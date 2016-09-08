#include <iostream>
#include "gtest/gtest.h"

#include "server/Server.h"

TEST(TestFunction, ReturnsXPlusOne)
{
    int result = Server::TestFunction(7);
    EXPECT_EQ(8, result);
}

TEST(ProcessBuffer, ReturnsMinuxOneIfError)
{
    char testBuffer[50];
    Server server;
    int result = server.ProcessBuffer(testBuffer);
    EXPECT_EQ(result, -1);
}
