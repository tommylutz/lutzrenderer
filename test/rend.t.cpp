#include <gtest/gtest.h>
#include "image_mock.h"
#include <rend.h>

using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::_;

TEST(NoopTest, NoopTest)
{
    EXPECT_EQ(1,1);
}

TEST(RendererLineTest, SinglePixelTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(1,2,255)).Times(1);
    
    Renderer rend;
    rend.draw_line(img,1,2,1,2,255);
}

TEST(RendererLineTest, SinglePixelTestDifferentGrayLevelTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(1,2,100)).Times(1);
    
    Renderer rend;
    rend.draw_line(img,1,2,1,2,100);
}



TEST(RendererLineTest, HorizontalLineTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(1,5,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,5,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   1,5, 
                   2,5,
                   255);
}

TEST(RendererLineTest, BackwardsHorizontalLineTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(1,5,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,5,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   2,5, 
                   1,5,
                   255);
}

TEST(RendererLineTest, DiagonalLineTestBottomLeftToTopRight)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(2,4,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,3,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   1,3, 
                   2,4,
                   255);
}

TEST(RendererLineTest, DiagonalLineTestTopLeftToBottomRight)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(2,9,255)).Times(1);
    EXPECT_CALL(img, set_pixel(3,8,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   2,9, 
                   3,8,
                   255);
}

TEST(RendererLineTest, DiagonalLineTestTopRightToBottomLeft)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(3,9,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,8,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   3,9, 
                   2,8,
                   255);
}

TEST(RendererLineTest, DiagonalLineTestBottomRightToTopLeft)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(3,9,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,8,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   3,9, 
                   2,8,
                   255);
}

TEST(RendererLineTest, VerticalLineTestTopToBottom)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(2,9,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,8,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   2,9, 
                   2,8,
                   255);
}

TEST(RendererLineTest, VerticalLineTestBottomToTop)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(2,8,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,9,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   2,8, 
                   2,9,
                   255);
}

TEST(RendererLineTest, ShortShallowLineTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(0,0,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,0,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,1,255)).Times(1);
    EXPECT_CALL(img, set_pixel(3,1,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   0,0, 
                   3,1,
                   255);
}

TEST(RendererLineTest, LongShallowLineTest)
{
    MockImage img;
    
    EXPECT_CALL(img, set_pixel(0,0,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,0,255)).Times(1);
    EXPECT_CALL(img, set_pixel(2,1,255)).Times(1);
    EXPECT_CALL(img, set_pixel(3,1,255)).Times(1);
    EXPECT_CALL(img, set_pixel(4,1,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   0,0, 
                   4,1,
                   255);
}

TEST(RendererLineTest, LongSteepLineTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(0,0,255)).Times(1);
    EXPECT_CALL(img, set_pixel(0,1,255)).Times(1);
    EXPECT_CALL(img, set_pixel(0,2,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,3,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,4,255)).Times(1);
    EXPECT_CALL(img, set_pixel(1,5,255)).Times(1);
    Renderer rend;
    rend.draw_line(img,
                   0,0, 
                   1,5,
                   255);
}



TEST(PolyTracer, DrawLineOrdered)
{
    MockImage img;
    Renderer rend;

    {
        InSequence dummy;
        EXPECT_CALL(img, set_pixel(0,0,255)).Times(1);
        EXPECT_CALL(img, set_pixel(0,1,255)).Times(1);
        EXPECT_CALL(img, set_pixel(0,2,255)).Times(1);
        EXPECT_CALL(img, set_pixel(1,3,255)).Times(1);
        EXPECT_CALL(img, set_pixel(1,4,255)).Times(1);
        EXPECT_CALL(img, set_pixel(1,5,255)).Times(1);
    }
    rend.draw_line( img,
                    0, 0,
                    1, 5,
                    255 );
}

TEST(PolyTracer, DrawLineOrdered_Long)
{
    MockImage img;
    Renderer rend;

    {
        InSequence dummy;
        EXPECT_CALL(img, set_pixel(1, 1,255)).Times(1);
        EXPECT_CALL(img, set_pixel(2, 1,255)).Times(1);
        EXPECT_CALL(img, set_pixel(3, 2,255)).Times(1);
        EXPECT_CALL(img, set_pixel(4, 2,255)).Times(1);
        EXPECT_CALL(img, set_pixel(5, 3,255)).Times(1);
        EXPECT_CALL(img, set_pixel(6, 3,255)).Times(1);
        EXPECT_CALL(img, set_pixel(7, 3,255)).Times(1);
        EXPECT_CALL(img, set_pixel(8, 4,255)).Times(1);
        EXPECT_CALL(img, set_pixel(9, 4,255)).Times(1);
        EXPECT_CALL(img, set_pixel(10,5,255)).Times(1);
        EXPECT_CALL(img, set_pixel(11,5,255)).Times(1);
    }
    rend.draw_line( img,
                    1,  1,
                    11, 5,
                    255 );
}

TEST(RendererFillTest, FillTriangle)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(0,0,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(1,0,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(2,0,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(3,0,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(4,0,255)).Times(AtLeast(1));

    EXPECT_CALL(img, set_pixel(1,1,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(2,1,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(3,1,255)).Times(AtLeast(1));
 
    EXPECT_CALL(img, set_pixel(2,2,255)).Times(AtLeast(1));

    Renderer rend;
    rend.fill_triangle(img, 
                       0,0,
                       2,2,
                       4,0,
                       255);
}

TEST(RendererFillTest, FillTriangleUpsideDown)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(10,10,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(11,10,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(12,10,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(13,10,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(14,10,255)).Times(AtLeast(1));
    EXPECT_CALL(img, set_pixel(12,9,255)).Times(AtLeast(1));

    Renderer rend;
    rend.fill_triangle(img, 
                       10,10,
                       14,10,
                       12,9,
                       255);
}

TEST(RendererFillTest, FillTriangleSinglePixel)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(10,10,255)).Times(1);
    Renderer rend;
    rend.fill_triangle(img, 
                       10,10,
                       10,10,
                       10,10,
                       255);
}

TEST(RendererFillTest, FillTriangle3Pixels)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(-1,5,255)).Times(1);
    EXPECT_CALL(img, set_pixel(0,5,255)).Times(1);
    EXPECT_CALL(img, set_pixel(-1,6,255)).Times(1);
    Renderer rend;
    rend.fill_triangle(img, 
                       -1,5,
                       0,5,
                       -1,6,
                       255);
}

TEST(RendererFillTest, FillTriangleWhereNextPixelIsSameForBothCursors)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(_,_,_)).Times(AtLeast(150));
    Renderer rend;
    rend.fill_triangle(img,
                       1,0,
                       0,100,
                       2,100,
                       255);
}



