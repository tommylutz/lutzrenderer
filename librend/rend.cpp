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
    img.set_pixel(1,1,255);

}

