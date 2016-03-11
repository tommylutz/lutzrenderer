#include <gtest/gtest.h>
#include "image_mock.h"

TEST(NoopTest, NoopTest)
{
    EXPECT_EQ(1,1);
}

TEST(NoopTest, FailTest)
{
    EXPECT_EQ(1,0);
}


