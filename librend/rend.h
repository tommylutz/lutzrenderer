#ifndef _REND_H_
#define _REND_H_
#include "image_interface.h"
#include <algorithm>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void draw_line(ImageInterface& img, 
                   int x0, int y0, 
                   int x1, int y1,
                   const Color& color);
    void draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   const Color& color);
    void fill_triangle(ImageInterface &img,
                   int x0, int y0, 
                   int x1, int y1,
                   int x2, int y2,
                   const Color& color);

    template <typename T>
    void fill_triangle(ImageInterface & img,
                       const T& p1,
                       const T& p2,
                       const T& p3,
                       const Color& color)
    {
        if(p1.y() <= p2.y() && p1.y() <= p3.y())
        {
            fill_triangle(  img, 
                            p1.x(), p1.y(),
                            p2.x(), p2.y(),
                            p3.x(), p3.y(),
                            color);
        }
        else if(p2.y() <= p1.y() && p2.y() <= p3.y())
        {
            fill_triangle(  img, 
                            p2.x(), p2.y(),
                            p1.x(), p1.y(),
                            p3.x(), p3.y(),
                            color);
        }
        else
        {
            fill_triangle(  img, 
                            p3.x(), p3.y(),
                            p1.x(), p1.y(),
                            p2.x(), p2.y(),
                            color);
        }
    }


    template <typename T>
    void draw_triangle(ImageInterface & img,
                       const T& p1,
                       const T& p2,
                       const T& p3,
                       const Color& color)
    {
        draw_line(img, p1.x(), p1.y(), p2.x(), p2.y(), color);
        draw_line(img, p2.x(), p2.y(), p3.x(), p3.y(), color);
        draw_line(img, p3.x(), p3.y(), p1.x(), p1.y(), color);
    }
};



#endif

