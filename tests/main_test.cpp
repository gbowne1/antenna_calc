#include <gtest/gtest.h>
#include "utils.h"

TEST(UtilsTest, Sha256) {
    antennacalc::Utils utils;
    EXPECT_EQ(utils.sha256("test"), "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
