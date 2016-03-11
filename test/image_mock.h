#include <gmock/gmock.h>
#include <image_interface.h>

class MockImage : public ImageInterface
{
    MOCK_METHOD3(set_pixel, void (int,int,unsigned char));
};
