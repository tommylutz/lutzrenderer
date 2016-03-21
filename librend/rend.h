#ifndef _REND_H_
#define _REND_H_
#include "image_interface.h"
#include <algorithm>
#include "model.h"
#include "vec3.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool is_face_filtered(const Vec3f& v1,
                          const Vec3f& v2,
                          const Vec3f& v3) const;

    void draw_line(ImageInterface& img, 
                   int x0, int y0, 
                   int x1, int y1,
                   const Color& color);
    void draw_line(ImageInterface& img,
                   double x0, double y0, 
                   double x1, double y1,
                   const Color& color);
    void fill_triangle(ImageInterface &img,
                   int x0, int y0, 
                   int x1, int y1,
                   int x2, int y2,
                   const Color& color);
    void fill_triangle_barycentric(ImageInterface &img,
                   double x0, double y0, 
                   double x1, double y1,
                   double x2, double y2,
                   const Color& color);
    template <typename T>
    void fill_triangle(ImageInterface & img,
                       const T& p1,
                       const T& p2,
                       const T& p3,
                       const Color& color)
    {
        fill_triangle_barycentric(img,
                     p1.x(),p1.y(),
                     p2.x(),p2.y(),
                     p3.x(),p3.y(),
                     color);
    }


    template <typename T>
    void draw_triangle(ImageInterface & img,
                       const T& p1,
                       const T& p2,
                       const T& p3,
                       const Color& color)
    {
        draw_line(img, p1.x(), p1.y(), p2.x(), p2.y(), color);
        draw_line(img, p2.x(), p2.y(), p3.x(), p3.y(), color);
        draw_line(img, p3.x(), p3.y(), p1.x(), p1.y(), color);
    }

    void render_wireframe_model(ImageInterface & img,
                                const Model & model);

    void render_random_color_model(ImageInterface & img,
                                   const Model & model);

    void render_flat_shaded_model(ImageInterface & img,
                                  const Model & model,
                                  const Vec3f& light_dir);
};



#endif

