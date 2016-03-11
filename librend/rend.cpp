#include <rend.h>
#include <iostream>
#include "image_interface.h"

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
    img.set_pixel(x0,y0,graylevel);

}

