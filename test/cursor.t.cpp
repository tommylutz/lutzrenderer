#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cursor.h>

TEST(Cursor, CursorTest)
{
    Cursor cursor;
    cursor.add_point(0,0);
    cursor.add_point(3,0);
    cursor.add_point(0,3);
    
    int x, y;
    bool did_y_change;
    
    while(!cursor.done())
    {
        cursor.advance(&did_y_change, &x, &y);
        printf("Point: %d,%d, y changed? %c\n",x,y,did_y_change?'Y':'N');
    }
    EXPECT_EQ(1,1);
    
}
