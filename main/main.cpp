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
        printf("Total vertexes: %d\nTotal faces: %d\n",
                model.num_vertexes(), 
                model.num_faces());
        printf("Ranges:\n");
        printf(" x (%f to %f)\n", model.xrange().first, model.xrange().second);
        printf(" y (%f to %f)\n", model.yrange().first, model.yrange().second);
        printf(" z (%f to %f)\n", model.zrange().first, model.zrange().second);

        double xoff = -1.*model.xrange().first;
        double yoff = -1.*model.yrange().first;
        double zoff = -1.*model.zrange().first;

        PngImage img(1000,1000, &i_libpng, &i_file);
        
        double scale = (std::min(img.width(), img.height())-1.) / 
                       std::max(model.xrange().second - model.xrange().first,
                                model.yrange().second - model.yrange().first );

        printf("Offsets:\n x=%f\n y=%f\n z=%f\n scale=%f\n",
                xoff, yoff, zoff, scale);
    
        Renderer rend;

        const int num_faces = model.num_faces();
        for(int facenum=0; facenum<num_faces; ++facenum)
        {
            //TODO: This assumes each face has only 3 vertexes.
            const Face& face = model.face_at(facenum);
            Vertex v1 = model.vertex_at(face.id1()).translate(xoff,yoff,zoff,scale);
            Vertex v2 = model.vertex_at(face.id2()).translate(xoff,yoff,zoff,scale);
            Vertex v3 = model.vertex_at(face.id3()).translate(xoff,yoff,zoff,scale);
            
            printf("Rendering face %d\n",facenum);
            rend.fill_triangle(img, v1, v2, v3, (0xFF << 24)        | 
                                                (rand()%256 << 16)  | 
                                                (rand()%256 << 8)   |
                                                rand()%256 );
        }

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
