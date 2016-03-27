#ifndef _IMAGE_INTERFACE_H_
#define _IMAGE_INTERFACE_H_
#include "color.h"

#include <stdexcept>
#include <assert.h>

class ImageInterface
{
public:
    ImageInterface() : m_width(0), m_height(0), m_pzbuf(NULL) { }
    ImageInterface(int width, int height) : m_pzbuf(NULL)
    { 
        if(width <= 0 || height <= 0)
            throw std::invalid_argument("Invalid width/height provided");
        
        init(width,height);    
    }

    virtual ~ImageInterface() { if(m_pzbuf) delete[] m_pzbuf; }
    virtual bool get_pixel(int x, int y, Color& color_out) const { return false; }
    virtual void set_pixel(int x, int y, const Color& color) = 0;
    virtual void set_pixel_zbuf(int x, int y, float z, const Color& color)
    {
        assert(m_pzbuf);
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
    void init(int width, int height)
    {
        m_width = width;
        m_height = height;

        if(m_pzbuf)
            delete[] m_pzbuf;
        m_pzbuf = new float[m_width*m_height]; 
        for(int i=0; i<m_width*m_height; ++i)
        {
            m_pzbuf[i] = -1e12;
        }
    }

    int m_width;
    int m_height;
    float * m_pzbuf;
    
};

#endif

