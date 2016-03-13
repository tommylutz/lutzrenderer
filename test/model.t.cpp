#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mock_file_interface.h>
#include <model.h>

using ::testing::_;
using ::testing::StrEq;
using ::testing::NotNull;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::DoAll;

void Expect_Fopen_Fgets_Fclose(const char * const * lines, Mockfile_Interface& i_file)
{
    static char buf[1];
    EXPECT_CALL(i_file, fopen(_,StrEq("rb"))).Times(1);
    auto & mock_fgets = 
        EXPECT_CALL(i_file, fgets(NotNull(),_,_));

    for(int i=0; lines[i]; ++i)
    {
        const char * line = lines[i];
        mock_fgets
            .WillOnce(DoAll(
                Invoke(
                    [line](char *s, int size, FILE * stream)
                    {
                        strncpy(s, line, size);
                    }),
                Return(buf))
            );
    }
    mock_fgets.WillRepeatedly(Return((char*)NULL));
    
    EXPECT_CALL(i_file, fclose(_)).WillRepeatedly(Return(0));
}

TEST(Model, ModelReadsFile)
{
    Mockfile_Interface i_file;
    const char * const fileLines[] = 
        {   "v 1 2 3\n"        ,
            "Another line\n"   ,
            "foo bar bat baz\n",
            NULL 
        };
    Model model;
    Expect_Fopen_Fgets_Fclose(fileLines, i_file);

    //TODO: Mock the file api to dole out the lines from the array above
    EXPECT_EQ(1,model.load_from_file("dummy.obj",i_file));
}
