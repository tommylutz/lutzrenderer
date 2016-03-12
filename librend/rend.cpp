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

void Renderer::draw_line(ImageInterface &img,
                         int x0, int y0,
                         int x1, int y1,
                         int graylevel)
{
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

