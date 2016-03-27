#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <external_interfaces/libtga_interface.h>
#include <image_tga.h>

TEST(TgaImage, RealFileOpen)
{
    libtga_Interface tga_real;
    TgaImage img("/home/dev/work/lutzrenderer/build/tinyrenderer-src/obj/african_head/african_head_diffuse.tga",
                &tga_real);
    EXPECT_EQ(1,0);
}
