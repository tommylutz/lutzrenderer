#ifndef _IMAGE_INTERFACE_H_
#define _IMAGE_INTERFACE_H_

class ImageInterface
{
public:
    virtual ~ImageInterface() { }
    virtual void set_pixel(int x, int y, unsigned char graylevel) = 0;
    
};

#endif

