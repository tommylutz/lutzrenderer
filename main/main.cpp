#include <iostream>
#include <rend.h>
#include <image_png.h>
#include <model.h>

void draw_sample_image(const char * filename)
{
    libpng_Interface i_libpng;
    file_Interface i_file;;
    PngImage img(1000,1000, &i_libpng, &i_file);
    Renderer rend;
    
    for(int x=0; x<1000; x+=10)
    {
        rend.draw_line(img, x, 0, 999, x, 0xFF0000FF); 
        rend.draw_line(img, 0, x, x, 999, 0xFFFF00FF); 
    }

    rend.draw_line(img, 0,   0,  999, 999, 0xFF00FFFF);
    rend.draw_line(img, 999, 0,  0,   999, 0xFFFFFFFF);

    rend.draw_line(img, 0,   0,   0,   999, 0xFF0000FF);
    rend.draw_line(img, 0,   999, 999, 999, 0xFF0000FF);
    rend.draw_line(img, 999, 999, 999, 0,   0xFF0000FF);
    rend.draw_line(img, 999, 0,   0,   0,   0xFF0000FF);

    rend.fill_triangle(img, 
                        100, 100,
                        50,  200,
                        150, 240,
                        0xFF00FF00);

    img.write(filename);
}


int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Drawing sample image to ./foo.png\n");
        draw_sample_image("./foo.png");
        return 0;
    }
    else
    {
        libpng_Interface i_libpng;
        file_Interface i_file;;
        printf("Attempting to load model from file [%s]\n",argv[1]);
        Model model;
        if(!model.load_from_file(argv[1], i_file))
        {
            printf("Failed to load model\n");
            return 1;
        }
        PngImage img(1000,1000, &i_libpng, &i_file);
        Renderer rend;
        rend.render_random_color_model(img, model);
        rend.render_wireframe_model(img, model);
        if(img.write("./foo.png"))
        {
            printf("Wrote an x-y plot of your model to ./foo.png!\n");
        }
        else
        {
            printf("Failed to write ./foo.png!\n");
        }
    }
        
    return 0;
}
