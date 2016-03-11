#ifndef _REND_H_
#define _REND_H_
#include "image_interface.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void draw_line(ImageInterface& img, 
                   int x0, int y0, 
                   int x1, int y1,
                   int graylevel);
};



#endif

