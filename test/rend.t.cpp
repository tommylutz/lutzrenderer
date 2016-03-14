#include <gtest/gtest.h>
#include "image_mock.h"
#include <rend.h>

using ::testing::AtLeast;

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
