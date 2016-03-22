#ifndef _IMAGE_INTERFACE_H_
#define _IMAGE_INTERFACE_H_
#include "color.h"

class ImageInterface
{
public:
    ImageInterface(int width, int height) : 
        m_width(width), 
        m_height(height) 
    { 
        m_pzbuf = new float[m_width*m_height]; 
        for(int i=0; i<m_width*m_height; ++i)
        {
            m_pzbuf[i] = -1e12;
        }
    }
    virtual ~ImageInterface() { delete[] m_pzbuf; }
    virtual void set_pixel(int x, int y, const Color& color) = 0;
    virtual void set_pixel_zbuf(int x, int y, float z, const Color& color)
    {
        const int zbufidx = x+y*m_width;
        if(x < m_width && y < m_height &&
           x >= 0 && y >= 0 && z>m_pzbuf[zbufidx])
        {
            m_pzbuf[zbufidx] = z;
            set_pixel(x,y,color);
        }
    }
    int width() const  { return m_width;  }
    int height() const { return m_height; } 
protected:
    int m_width;
    int m_height;
    float * m_pzbuf;
    
};

#endif

