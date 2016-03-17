#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cursor.h>

TEST(Cursor, EmptyCursor)
{
    Cursor cursor;
    EXPECT_FALSE(cursor.advance());
}

TEST(Cursor, PointCursor)
{
    Cursor cursor;
    cursor.add_point(1,5);
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(1,cursor.x());
    EXPECT_EQ(5,cursor.y());
    EXPECT_FALSE(cursor.advance());
}

TEST(Cursor, ShortLine)
{
    Cursor cursor;
    cursor.add_point(0,0);
    cursor.add_point(1,0);
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(0,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(1,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_FALSE(cursor.advance());
    EXPECT_EQ(1,cursor.x()); EXPECT_EQ(0,cursor.y());
}

TEST(Cursor, NoLine)
{
    Cursor cursor;
    cursor.add_point(0,0);
    cursor.add_point(0,0);
    cursor.add_point(0,0);
    cursor.add_point(0,0);
    cursor.add_point(0,0);
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(0,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_FALSE(cursor.advance());
}

TEST(Cursor, PingPong)
{
    Cursor cursor;
    cursor.add_point(0,0);
    cursor.add_point(1,0);
    cursor.add_point(1,0);
    cursor.add_point(0,0);
    cursor.add_point(0,0);
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(0,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(1,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_TRUE(cursor.advance());
    EXPECT_EQ(0,cursor.x()); EXPECT_EQ(0,cursor.y());
    EXPECT_FALSE(cursor.advance());
    EXPECT_EQ(0,cursor.x()); EXPECT_EQ(0,cursor.y());
}
