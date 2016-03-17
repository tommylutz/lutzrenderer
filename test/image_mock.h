#ifndef IMAGE_MOCK_H_
#define IMAGE_MOCK_H_

#include <gmock/gmock.h>
#include <image_interface.h>

class MockImage : public ImageInterface
{
public:
    MockImage() : ImageInterface(0,0) { }
    MOCK_METHOD3(set_pixel, void (int,int,const Color& color));
    virtual ~MockImage() {}

};

#endif

