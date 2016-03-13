#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mock_file_interface.h>
#include <model.h>

TEST(Model, ModelReadsFile)
{
    const char * const fileLines[] = 
        {   "v 1 2 3",
            "f .....",
            NULL 
        };
    Model model;

    //TODO: Mock the file api to dole out the lines from the array above
    EXPECT_EQ(1,0);   
}
