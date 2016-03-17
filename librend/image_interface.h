#ifndef _IMAGE_INTERFACE_H_
#define _IMAGE_INTERFACE_H_
#include "color.h"

class ImageInterface
{
public:
    ImageInterface(int width, int height) : m_width(width), m_height(height) {}
    virtual ~ImageInterface() { }
    virtual void set_pixel(int x, int y, const Color& color) = 0;
    int width() const  { return m_width;  }
    int height() const { return m_height; } 
protected:
    int m_width;
    int m_height;
    
};

#endif

