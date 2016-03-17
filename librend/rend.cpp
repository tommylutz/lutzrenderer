#include <rend.h>
#include <iostream>
#include "image_interface.h"
#include <math.h>
#include <stdlib.h>
#include "cursor.h"
#include <assert.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   const Color& color)
{
    draw_line(  img,
                static_cast<int>(round(x0)), static_cast<int>(round(y0)),
                static_cast<int>(round(x1)), static_cast<int>(round(y1)),
                color );
}

void Renderer::draw_line(ImageInterface& img,
                    int x0, int y0,
                    int x1, int y1,
                    const Color& color)
{
    const int dx = abs(x1 - x0);
    const int dy = abs(y1 - y0);
    const int dx2 = dx << 1;
    const int dy2 = dy << 1;
    const int y_sign = (y1>=y0)?1:-1;
    const int x_sign = (x1>=x0)?1:-1;
    int error = 0;

    if(dx > dy)
    {   
        int y = y0;
        for(int x=x0; x != (x1+x_sign); x += x_sign)
        {
            img.set_pixel(x,y,color);
            error += dy2;
            if(error >= dx)
            {
                y += y_sign;
                error -= dx2;
            }
        }
    }
    else
    {
        int x = x0;
        for(int y=y0; y != (y1+y_sign); y += y_sign)
        {
            img.set_pixel(x,y,color);
            error += dx2;
            if(error >= dy)
            {
                x += x_sign;
                error -= dy2;
            }
        }
    }
}

void Renderer::fill_triangle(ImageInterface &img,
               int x0, int y0, 
               int x1, int y1,
               int x2, int y2,
               const Color& color)
{
    //Assume: x0,y0 is the lowest point
    Cursor c1;
    c1.add_point(x0,y0);
    c1.add_point(x1,y1);
    c1.add_point(x2,y2);

    Cursor c2;
    c2.add_point(x0,y0);
    c2.add_point(x2,y2);
    c2.add_point(x1,y1);
    
    bool did_y_change;
    int x,y;
    c1.advance(&did_y_change, &x, &y);
    c2.advance(&did_y_change, &x, &y);
    Renderer rend;
    
    while(true)
    {
        printf("a c1: %3d,%3d c2: %3d,%3d\n",c1.x(),c1.y(), c2.x(), c2.y());
        rend.draw_line(img, c1.x(), c1.y(), c2.x(), c2.y(), color);
        did_y_change = false;
        while(!c1.done() && !did_y_change)
        {
            c1.advance(&did_y_change, &x, &y);
            img.set_pixel(x,y,color);
        }
        printf("b c1: %3d,%3d c2: %3d,%3d\n",c1.x(),c1.y(), c2.x(), c2.y());
        did_y_change = false;
        while(!c2.done() && !did_y_change)
        {
            c2.advance(&did_y_change, &x, &y);
            img.set_pixel(x,y,color);
        }
        printf("c c1: %3d,%3d c2: %3d,%3d\n",c1.x(),c1.y(), c2.x(), c2.y());

        if(c2.done() || c1.done())
            break;

    }
    
}
