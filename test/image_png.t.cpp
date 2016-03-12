#include <gtest/gtest.h>
#include <gmock/gmock.h>
//NOTE: to avoid linking gmock into main library, above #include is necessary
//before including the mock interfaces
#include <mock_libpng_interface.h>
#include <mock_file_interface.h>

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

TEST_F(ImagePngFixture, ImagePngConstructor)
{
    EXPECT_EQ(1,0) << "Leaving myself a failing test";
}
