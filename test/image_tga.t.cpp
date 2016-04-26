#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <external_interfaces/libtga_interface.h>
#include <external_interfaces/mock_libtga_interface.h>
#include <image_tga.h>
#include <string.h>

using ::testing::StrEq;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::_;

MATCHER_P(TgaDataFlagsEqual, other, "")
{
    return arg->flags == other->flags;
}

ACTION_P(SetImageData,tgahdr)
{
    TGAData * tgadata = arg1;
    const int nBytes = tgahdr->width*
                       tgahdr->height*
                       tgahdr->depth/8;
    tgadata->img_data = new tbyte[nBytes];

    for(int i=0; i<nBytes; ++i)
        tgadata->img_data[i] = i;
}

TEST(TgaImage, ConstructTgaImage)
{
    TGA dummyTga;
    memset(&dummyTga,0,sizeof(dummyTga));
    dummyTga.hdr.width = 100;
    dummyTga.hdr.height = 50;
    dummyTga.hdr.depth = 8;
    dummyTga.hdr.alpha = 0;
    TGAData lclTgaData;
    memset(&lclTgaData,0,sizeof(TGAData));
    lclTgaData.flags |= TGA_RGB;
    lclTgaData.flags |= TGA_IMAGE_ID;
    lclTgaData.flags |= TGA_COLOR_MAP;
    lclTgaData.flags |= TGA_IMAGE_DATA;    
    
    dummyTga.error = NULL;
    Mocklibtga_Interface tga_mock;

    EXPECT_CALL(tga_mock, TGAOpen(StrEq("somefile.tga"),StrEq("rb"))).
        Times(1).WillOnce(Return(&dummyTga));
    ON_CALL(tga_mock,TGAReadImage(_,_)).WillByDefault(Return(TGA_ERROR));
    EXPECT_CALL(tga_mock, TGAReadImage(_,TgaDataFlagsEqual(&lclTgaData))).
        Times(1).WillOnce(DoAll(
                            SetImageData(&dummyTga.hdr),
                            Return(TGA_OK)));
    EXPECT_CALL(tga_mock,TGAClose(_)).Times(1);

    TgaImage img("somefile.tga",
                &tga_mock);
    
    Color color;
    EXPECT_TRUE(img.get_pixel(0,0,color));
    EXPECT_EQ(0xFF020100,color);
    EXPECT_TRUE(img.get_pixel(1,0,color));
    EXPECT_EQ(0xFF050403,color);
}
