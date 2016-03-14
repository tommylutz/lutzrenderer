#include <rend.h>
#include <iostream>
#include "image_interface.h"
#include <math.h>
#include <stdlib.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   int graylevel)
{
    draw_line(  img,
                static_cast<int>(round(x0)), static_cast<int>(round(y0)),
                static_cast<int>(round(x1)), static_cast<int>(round(y1)),
                graylevel );
}


void Renderer::draw_line(ImageInterface &img,
                         int x0, int y0,
                         int x1, int y1,
                         int graylevel)
{
    draw_line_ordered(img,x0,y0,x1,y1,graylevel);
    return;
    //TODO: See how lean we can get this function. Use valgrind or other
    //profiling tools. The tutorial shows a methoid for eliminating all floating point 
    //variables in this func. No multiplications or divisions
    const bool x_and_y_swapped = 
        normalize_coordinates_for_drawing_line(x0, y0, x1, y1);

    float pct_done = 0;
    const float y_total_dist = ((float)(y1-y0));
    const float x_total_dist = ((float)(x1-x0));

    for(int x=x0; x<=x1; ++x)
    {
        pct_done = x_total_dist?(((float)(x-x0))/x_total_dist):0;
        int y = round(y0+pct_done*y_total_dist);
        if(x_and_y_swapped)
            img.set_pixel(y,x,graylevel);
        else
            img.set_pixel(x,y,graylevel);
    }
}

void Renderer::draw_line_ordered(ImageInterface &img,
                         int x0, int y0,
                         int x1, int y1,
                         int graylevel)
{
    int dx = x1-x0;
    int dy = y1-y0;
    int x = x0, y = y0;
    
    int * axis_to_sweep;
    int axis_increment;
    int axis_target;

    int error = 0;
    int error_accumulator = 0;
    int *error_axis;
    int error_increment;
    int error_threshold;

    if(abs(dx) > abs(dy))
    {
        axis_to_sweep = &x;
        axis_increment = (dx<0)?-1:1;
        axis_target = x1 + axis_increment;

        error = abs(dy) << 1;
        error_threshold = abs(dx);
        error_axis = &y;
        error_increment = (dy<0)?-1:1;
    }
    else
    {
        axis_to_sweep = &y;
        axis_increment = (dy<0)?-1:1;
        axis_target = y1 + axis_increment;

        error = abs(dx) << 1;
        error_threshold = abs(dy);
        error_axis = &x;
        error_increment = (dx<0)?-1:1;
    }
    
    do
    {
        /*printf("Plot (%d,%d) ErrorAcc %d Error %d Thresh %d\n",
                x,y,
                error_accumulator,
                error,
                error_threshold);*/
        img.set_pixel(x,y,graylevel);
        
        error_accumulator += error;
        if(error_threshold &&  //protect against horizontal/vertical line
           error_accumulator >= error_threshold)
        {
            *error_axis += error_increment;
            while(error_accumulator >= 0)
                error_accumulator -= error_threshold;
        }
        
        *axis_to_sweep += axis_increment;
    } while(*axis_to_sweep != axis_target);

}

void Renderer::fill_triangle(ImageInterface &img,
               int x0, int y0, 
               int x1, int y1,
               int x2, int y2,
               int graylevel)
{
}
