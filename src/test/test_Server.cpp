#include <iostream>
#include "gtest/gtest.h"

#include "server/Server.h"

TEST(TestFunction, ReturnsXPlusOne) {
    int result = Server::TestFunction(7);
    EXPECT_EQ(8, result);
}

TEST(TestFunction, PassOnNotEqual) {
    EXPECT_NE(6, 7);
}