#include <iostream>
#include <rend.h>
#include <image_png.h>

int main(int argc, char ** argv)
{
    std::cout << "Hello world\n";
    libpng_Interface i_libpng;
    file_Interface i_file;;
    PngImage img(100,100, &i_libpng, &i_file);
    Renderer rend;
    rend.draw_line(img, 0,  0,  99, 99, 255);
    rend.draw_line(img, 99, 0,  0,  99, 255);

    rend.draw_line(img, 0,  0,  0,  99, 255);
    rend.draw_line(img, 0,  99, 99, 99, 255);
    rend.draw_line(img, 99, 99, 99, 0,  255);
    rend.draw_line(img, 99, 0,  0,  0,  255);

    img.write("./foo.png");
    return 0;
}
