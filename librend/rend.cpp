#include <rend.h>
#include <iostream>
#include "image_interface.h"
#include <math.h>
#include <stdlib.h>
#include "cursor.h"
#include <assert.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::is_face_filtered(const Vec3f& v1,
                          const Vec3f& v2,
                          const Vec3f& v3) const
{
    return false; //comment this out to restrict the rendering to a region

    //This function is useful for debugging pieces of the image that don't appear correct.
    //By constricting the X/Y/Z range of what will actually be rendered (in model coordinates),
    //we can make the code run for a single face that appears incorrect, to find out exactly 
    //what has gone wrong.
    const double Z_MIN = 0.6;
    const double Z_MAX = 2.0;
    const double X_MIN = -0.1;
    const double X_MAX = 0.02;
    const double Y_MIN = -0.04;
    const double Y_MAX = 0.0;

    if(
        v1.x() > X_MAX || v2.x() > X_MAX || v3.x() > X_MAX ||
        v1.x() < X_MIN || v2.x() < X_MIN || v3.x() < X_MIN ||
        v1.y() > Y_MAX || v2.y() > Y_MAX || v3.y() > Y_MAX ||
        v1.y() < Y_MIN || v2.y() < Y_MIN || v3.y() < Y_MIN ||
        v1.z() > Z_MAX || v2.z() > Z_MAX || v3.z() > Z_MAX ||
        v1.z() < Z_MIN || v2.z() < Z_MIN || v3.z() < Z_MIN)
    {
        return true;
    }
    return false;
}

void Renderer::draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   const Color& color)
{
    draw_line(  img,
                static_cast<int>(round(x0)), static_cast<int>(round(y0)),
                static_cast<int>(round(x1)), static_cast<int>(round(y1)),
                color );
}

void Renderer::draw_line(ImageInterface& img,
                    int x0, int y0,
                    int x1, int y1,
                    const Color& color)
{
    Cursor cursor;
    cursor.add_point(x0,y0);
    cursor.add_point(x1,y1);
    while(cursor.advance())
    {
        img.set_pixel(cursor.x(),cursor.y(),color);
    }
    return;
}

void Renderer::fill_triangle_barycentric_zbuf(ImageInterface &img,
                   const Vec3f& p1,
                   const Vec3f& p2,
                   const Vec3f& p3,
                   const Color& color)
{
    const double x0 = p1.x();
    const double y0 = p1.y();
    const double x1 = p2.x();
    const double y1 = p2.y();
    const double x2 = p3.x();
    const double y2 = p3.y();
    const int x_min = std::max(0,(int)floor(std::min(x0,std::min(x1,x2))));
    const int x_max = std::min(img.width()-1,(int)ceil(std::max(x0,std::max(x1,x2))));
    const int y_min = std::max(0,(int)floor(std::min(y0,std::min(y1,y2))));
    const int y_max = std::min(img.height()-1,(int)ceil(std::max(y0,std::max(y1,y2))));
    
    /*printf("Fill triangle bounding box (%d->%d) y (%d->%d)\n",x_min,x_max,y_min,y_max);
    printf("Triangle: (%.3f,%.3f), (%.3f,%.3f), (%.3f,%.3f)\n",
            x0,y0,
            x1,y1,
            x2,y2);*/

    for(int y=y_min; y<=y_max; ++y)
    {
        for(int x=x_min; x<=x_max; ++x)
        {
            const Vec3f v1(x2-x0, x1-x0, x0-(double)x);
            const Vec3f v2(y2-y0, y1-y0, y0-(double)y);
            const Vec3f crossprod = v1^v2;
            if(std::abs(crossprod.z()) >= 0.01)
            {
                Vec3f barycoords(1. - (crossprod.x() + crossprod.y())/crossprod.z(),
                                 crossprod.y()/crossprod.z(),
                                 crossprod.x()/crossprod.z());
                /*std::cout << "x=" << x << ", y=" << y 
                          << ", Crossproduct of " << v1 << " and " << v2 
                          << " is " << crossprod << ", bary: " << barycoords << ": ";*/
                const Vec3f z_values(p1.z(), p2.z(), p3.z());
                float z_value = z_values * barycoords;

                if(barycoords.x() >= 0 &&
                   barycoords.y() >= 0 &&
                   barycoords.z() >= 0)
                {
                    img.set_pixel_zbuf(x,y,z_value,color);
                }
                else
                {
                }

            }
            else
            {
                printf("ERROR: Found degenerate triangle\n");
                std::cout << p1 << ", " << p2 << ", " << p3 << ", v1=" << v1 << ", v2=" << v2 << "\n";
            }
            
        }
    }
    
}




void Renderer::fill_triangle_barycentric(ImageInterface &img,
               double x0, double y0, 
               double x1, double y1,
               double x2, double y2,
               const Color& color)
{
    const int x_min = std::max(0,(int)floor(std::min(x0,std::min(x1,x2))));
    const int x_max = std::min(img.width()-1,(int)ceil(std::max(x0,std::max(x1,x2))));
    const int y_min = std::max(0,(int)floor(std::min(y0,std::min(y1,y2))));
    const int y_max = std::min(img.height()-1,(int)ceil(std::max(y0,std::max(y1,y2))));
    
    /*printf("Fill triangle bounding box (%d->%d) y (%d->%d)\n",x_min,x_max,y_min,y_max);
    printf("Triangle: (%.3f,%.3f), (%.3f,%.3f), (%.3f,%.3f)\n",
            x0,y0,
            x1,y1,
            x2,y2);*/

    for(int y=y_min; y<=y_max; ++y)
    {
        for(int x=x_min; x<=x_max; ++x)
        {
            Vec3f v1(x2-x0, x1-x0, x0-(double)x);
            Vec3f v2(y2-y0, y1-y0, y0-(double)y);
            Vec3f crossprod = v1^v2;
            if(std::abs(crossprod.z()) >= 1e-12)
            {
                Vec3f barycoords(1. - (crossprod.x() + crossprod.y())/crossprod.z(),
                                 crossprod.y()/crossprod.z(),
                                 crossprod.x()/crossprod.z());
                /*std::cout << "x=" << x << ", y=" << y 
                          << ", Crossproduct of " << v1 << " and " << v2 
                          << " is " << crossprod << ", bary: " << barycoords << ": ";*/

                if(barycoords.x() >= 0 &&
                   barycoords.y() >= 0 &&
                   barycoords.z() >= 0)
                {
                    img.set_pixel(x,y,color);
                }
                else
                {
                }

            }
            else
            {
                printf("ERROR: Found degenerate triangle\n");
            }
            
        }
    }
    
}

void Renderer::fill_triangle(ImageInterface &img,
               double x0, double y0, 
               double x1, double y1,
               double x2, double y2,
               const Color& color)
{   
    return fill_triangle_barycentric(img,x0,y0,x1,y1,x2,y2,color);
}

void Renderer::render_wireframe_model(ImageInterface & img,
                                      const Model & model)
{
    Vec3f offset(-1*model.xrange().first,
                 -1*model.yrange().first,
                 0);
    double scale = (std::min(img.width(), img.height())-1.) / 
                   std::max(model.xrange().second - model.xrange().first,
                            model.yrange().second - model.yrange().first );
    
    const int num_faces = model.num_faces();

    for(int facenum = 0; facenum < num_faces; ++facenum)
    {
        const Face& face = model.face_at(facenum);
        Vec3f v1 = model.vertex_at(face.id1());
        Vec3f v2 = model.vertex_at(face.id2());
        Vec3f v3 = model.vertex_at(face.id3());

        if(is_face_filtered(v1,v2,v3))
            continue;
        
        draw_triangle(img,
                      (v1+offset)*scale,
                      (v2+offset)*scale,
                      (v3+offset)*scale,
                      0xffffffff);
    }
}

void Renderer::render_random_color_model(ImageInterface & img,
                                         const Model & model)
{
    Vec3f offset(-1*model.xrange().first,
                 -1*model.yrange().first,
                 0);
    double scale = (std::min(img.width(), img.height())-1.) / 
                   std::max(model.xrange().second - model.xrange().first,
                            model.yrange().second - model.yrange().first );
    const int num_faces = model.num_faces();

    for(int facenum = 0; facenum < num_faces; ++facenum)
    {
        const Face& face = model.face_at(facenum);
        Vec3f v1 = model.vertex_at(face.id1());
        Vec3f v2 = model.vertex_at(face.id2());
        Vec3f v3 = model.vertex_at(face.id3());

        fill_triangle(img,
                      (v1+offset)*scale,
                      (v2+offset)*scale,
                      (v3+offset)*scale,
                        (0xFF << 24)        | 
                        (rand()%256 << 16)  | 
                        (rand()%256 << 8)   |
                        rand()%256 );
    }
}


void Renderer::render_flat_shaded_model(ImageInterface & img,
                                        const Model & model,
                                        const Vec3f& light_dir)
{
    Vec3f offset(-1*model.xrange().first,
                 -1*model.yrange().first,
                 0);
    double scale = (std::min(img.width(), img.height())-1.) / 
                   std::max(model.xrange().second - model.xrange().first,
                            model.yrange().second - model.yrange().first );
    const int num_faces = model.num_faces();


    for(int facenum = 0; facenum < num_faces; ++facenum)
    {
        const Face& face = model.face_at(facenum);
        Vec3f v1 = model.vertex_at(face.id1());
        Vec3f v2 = model.vertex_at(face.id2());
        Vec3f v3 = model.vertex_at(face.id3());

        if(is_face_filtered(v1,v2,v3))
            continue;

        Vec3f normal = ((v2-v1)^(v3-v1)).normalize();
        double intensity = light_dir*normal;

        if(intensity > 0)
        {
            unsigned int graylevel = intensity*255;
            unsigned int color = 
                            graylevel      |
                            graylevel<<8   |
                            graylevel<< 16 |
                            0xFF000000;
            fill_triangle_barycentric_zbuf(img,
                          (v1+offset)*scale,
                          (v2+offset)*scale,
                          (v3+offset)*scale,
                          color );
        }
    }
}




