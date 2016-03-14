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
                   int graylevel);
    void draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   int graylevel);
    void fill_triangle(ImageInterface &img,
                   int x0, int y0, 
                   int x1, int y1,
                   int x2, int y2,
                   int graylevel);

    template <typename T>
    void draw_triangle(ImageInterface & img,
                       const T& p1,
                       const T& p2,
                       const T& p3,
                       int graylevel)
    {
        draw_line(img, p1.x(), p1.y(), p2.x(), p2.y(), graylevel);
        draw_line(img, p2.x(), p2.y(), p3.x(), p3.y(), graylevel);
        draw_line(img, p3.x(), p3.y(), p1.x(), p1.y(), graylevel);
    }
                    
private:
    inline bool normalize_coordinates_for_drawing_line(
                                        int &x0, int &y0,
                                        int &x1, int &y1)
    {
        //At the end of this function,
        // (1) x0 must be less or equal to x1
        // (2) x1-x0 must be greater than abs(y1-y0)
        //If we have swapped x and y coordinates in order to achieve (2),
        //we return true.
        if(abs(x0-x1) < abs(y0-y1))
        {   
            if(y0 > y1)
            {
                std::swap(x0,y1);
                std::swap(x1,y0);
            }
            else
            {
                std::swap(x0,y0);
                std::swap(x1,y1);
            }
            return true;
        }
        else if(x0 > x1)
        {
            std::swap(x0,x1);
            std::swap(y0,y1);
            return false;
        }
        else //Coordinates already met the postcondition
        {
            return false;
        }
    }
};



#endif

