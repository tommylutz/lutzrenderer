#include <gtest/gtest.h>
#include <gmock/gmock.h>
//NOTE: to avoid linking gmock into main library, above #include is necessary
//before including the mock interfaces
#include <mock_libpng_interface.h>
#include <mock_file_interface.h>
#include <image_png.h>

using ::testing::Return;
using ::testing::StrEq;
using ::testing::_;

#define DUMMY_FILEPTR ((FILE*)1)
#define DUMMY_PNG_STRUCTP ((png_structp)2)
#define DUMMY_PNG_INFOP ((png_infop)3)

class ImagePngFixture : public ::testing::Test
{
public:
    ImagePngFixture()
    {
        i_file = &m_mockfile;
        i_libpng = &m_mocklibpng;
    }
protected:
    Mocklibpng_Interface m_mocklibpng;
    libpng_Interface * i_libpng;

    Mockfile_Interface m_mockfile;
    file_Interface * i_file;
};

TEST_F(ImagePngFixture, PixelCount)
{
    PngImage img(100,100, i_libpng, i_file);
    EXPECT_EQ(10000, img.num_pixels());
}

TEST_F(ImagePngFixture, WriteTest)
{
    EXPECT_CALL(m_mockfile, fclose(DUMMY_FILEPTR))
        .Times(1);

    EXPECT_CALL(m_mocklibpng, png_create_write_struct(_,_,_,_))
        .Times(1)
        .WillOnce(Return(DUMMY_PNG_STRUCTP));

    EXPECT_CALL(m_mocklibpng, png_create_info_struct(DUMMY_PNG_STRUCTP))
        .Times(1)
        .WillOnce(Return(DUMMY_PNG_INFOP));

    jmp_buf jb;
    EXPECT_CALL(m_mocklibpng, png_jmp_buf(_))
        .Times(1)
        .WillOnce(Return(&jb));

    EXPECT_CALL(m_mockfile, fopen(StrEq("foo.png"),StrEq("wb")))
        .Times(1)
        .WillOnce(Return(DUMMY_FILEPTR));

    EXPECT_CALL(m_mocklibpng, png_init_io(_,_))
        .Times(1);

    EXPECT_CALL(m_mocklibpng, png_set_IHDR(_,_,_,_,_,_,_,_,_))
        .Times(1);

    EXPECT_CALL(m_mocklibpng, png_set_rows(_,_,_))
        .Times(1);

    EXPECT_CALL(m_mocklibpng, png_write_png(_,_,_,_))
        .Times(1);

    EXPECT_CALL(m_mocklibpng, png_destroy_write_struct(_,_))
        .Times(1);

    PngImage img(100,100, i_libpng, i_file);
    EXPECT_TRUE(img.write("foo.png"));
}
