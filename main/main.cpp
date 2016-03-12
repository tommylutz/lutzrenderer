#include <iostream>
#include <rend.h>
#include <image_png.h>

int main(int argc, char ** argv)
{
    std::cout << "Hello world\n";
    libpng_Interface i_libpng;
    file_Interface i_file;;
    PngImage img(1000,1000, &i_libpng, &i_file);
    Renderer rend;
    
    for(int x=0; x<1000; x+=10)
    {
        rend.draw_line(img, x, 0, 999, x, abs(255-x/2)); 
        rend.draw_line(img, 0, x, x, 999, abs(255-x/2)); 
    }

    rend.draw_line(img, 0,   0,  999, 999, 255);
    rend.draw_line(img, 999, 0,  0,   999, 255);

    rend.draw_line(img, 0,   0,   0,   999, 255);
    rend.draw_line(img, 0,   999, 999, 999, 255);
    rend.draw_line(img, 999, 999, 999, 0,   255);
    rend.draw_line(img, 999, 0,   0,   0,   255);

    img.write("./foo.png");
    return 0;
}
