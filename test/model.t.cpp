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
    const char * const fileLines[] = { NULL  };
    Model model;
    Expect_Fopen_Fgets_Fclose(fileLines, i_file);

    EXPECT_TRUE(model.load_from_file("dummy.obj",i_file));
    EXPECT_EQ(0, model.num_vertexes());
    EXPECT_EQ(0, model.num_faces());
}

TEST(Model, ModelLoadsVertexes)
{
    Mockfile_Interface i_file;
    const char * const fileLines[] = 
        {   "v 1.234 2.512 -3.6381\n"        ,
            "v 2 3 4\n",
            "v 5 6 7\n",
            "Another line\n"   ,
            "foo bar bat baz\n",
            NULL 
        };
    Model model;
    Expect_Fopen_Fgets_Fclose(fileLines, i_file);

    EXPECT_TRUE(model.load_from_file("dummy.obj",i_file));
    ASSERT_EQ(3, model.num_vertexes());
    EXPECT_EQ(Vertex(1.234,2.512,-3.6381), model.vertex_at(0));
    EXPECT_EQ(Vertex(2,    3,     4     ), model.vertex_at(1));
    EXPECT_EQ(Vertex(5,    6,     7     ), model.vertex_at(2));
}

TEST(Model, ModelLoadsFaces)
{
    Mockfile_Interface i_file;
    const char * const fileLines[] = 
        {   "v 1.234 2.512 -3.6381\n"        ,
            "v 2 3 4\n",
            "v 5 6 7\n",
            "f 0/5/23 1/5/2 2/56/1\n",
            "Another line\n"   ,
            "foo bar bat baz\n",
            NULL
        };
    Model model;
    Expect_Fopen_Fgets_Fclose(fileLines, i_file);

    EXPECT_EQ(1,model.load_from_file("dummy.obj",i_file));
    EXPECT_EQ(3, model.num_vertexes());
    ASSERT_EQ(1, model.num_faces());
    EXPECT_EQ(Face(0,1,2),model.face_at(0));
}

