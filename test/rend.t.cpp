#include <gtest/gtest.h>
#include "image_mock.h"
#include <rend.h>

TEST(NoopTest, NoopTest)
{
    EXPECT_EQ(1,1);
}

TEST(RendererLineTest, SinglePixelTest)
{
    MockImage img;
    EXPECT_CALL(img, set_pixel(1,2,255)).Times(1);
    
    Renderer rend;
    rend.draw_line(img,1,2,3,4,255);
}

