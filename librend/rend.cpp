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
    Cursor cursor;
    cursor.add_point(x0,y0);
    cursor.add_point(x1,y1);
    while(cursor.advance())
    {
        img.set_pixel(cursor.x(),cursor.y(),color);
    }
    return;
}

void Renderer::fill_triangle(ImageInterface &img,
               int x0, int y0, 
               int x1, int y1,
               int x2, int y2,
               const Color& color)
{   
    if(y0 <= y1 && y0 <= y2)
    {
        //Good to go!
    }
    else if(y1 <= y0 && y1 <= y2)
    {
        //y1 is the minimum
        fill_triangle(img,
                      x1,y1,
                      x0,y0,
                      x2,y2,
                      color);
        return;
    }
    else
    {
        //y2 is the minimum
        fill_triangle(img,
                      x2,y2,
                      x0,y0,
                      x1,y1,
                      color);
        return;
    }

    //At this point, y0 is the lowest point
    Cursor c1;
    c1.add_point(x0,y0);
    c1.add_point(x1,y1);
    c1.add_point(x2,y2);

    Cursor c2;
    c2.add_point(x0,y0);
    c2.add_point(x2,y2);
    c2.add_point(x1,y1);
    
    Renderer rend;

    c1.advance();
    c2.advance();

    //TODO: Loop terminating condition can be optimized further
    // Cursors can go speeding past each other right now
    while(true)
    {
        rend.draw_line(img, c1.x(), c1.y(), c2.x(), c2.y(), color);
        
        int old_y = c1.y();
        while(c1.advance() && c1.y() == old_y)
            img.set_pixel(c1.x(),c1.y(),color);
        if(c1.y() < old_y)
            break;
        
        old_y = c2.y();
        while(c2.advance() && c2.y() == old_y)
            img.set_pixel(c2.x(),c2.y(),color);
        if(c2.y() < old_y)
            break;

        if(c1.done() || c2.done()) 
            break;
    }
    
}
