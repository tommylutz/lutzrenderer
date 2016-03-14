
#include "image_png.h"
#include "external_interfaces/libpng_interface.h"
#include "external_interfaces/file_interface.h"
#include <stdexcept>
#include <csetjmp>

PngImage::PngImage(
             int width,
             int height,
             libpng_Interface *p_i_libpng,
             file_Interface * p_i_file) :
    ImageInterface(width, height),
    i_libpng(p_i_libpng),
    i_file(p_i_file)
{
    //TODO: Move this error checking into base class
    if(width <= 0 || height <= 0)
        throw std::invalid_argument("Invalid width/height provided");

    m_image_data = new unsigned char[width*height];
    for(int i=0; i<width*height; ++i)
        m_image_data[i] = 0;
}

PngImage::~PngImage()
{
    delete[] m_image_data;
}

int PngImage::num_pixels() const
{
    return m_width * m_height;
}

void PngImage::set_pixel(int x, int y, unsigned char graylevel)
{
    if(x>=0 && x < m_width &&
       y>=0 && y < m_height)
    {
        m_image_data[x+y*m_width] = graylevel;
    }
}

bool PngImage::write(const std::string& strFilename)
{
    png_bytepp image_rows = NULL;
    FILE * file = i_file->fopen(strFilename.c_str(),"wb");
    if(!file)
        return false;

    png_structp png_ptr = 
        i_libpng->png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                (png_voidp)NULL, /* user_error_ptr */
                                NULL, /*user_error_fn*/
                                NULL /*user_warning_fn*/);
    if(!png_ptr)
    {
        i_file->fclose(file);
        return false;
    }

    png_infop info_ptr = i_libpng->png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        i_libpng->png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
        i_file->fclose(file);
        return false;
    }

    if(setjmp(*(i_libpng->png_jmp_buf(png_ptr))))
    {
        i_libpng->png_destroy_write_struct(&png_ptr,&info_ptr);
        i_file->fclose(file);
        if(image_rows)
        {
            delete[] image_rows;
        }
        return false;
    }

    i_libpng->png_init_io(png_ptr, file);

    i_libpng->png_set_IHDR(png_ptr, 
                 info_ptr, 
                 m_width, 
                 m_height, 
                 8 /*bit_depth*/,
                 PNG_COLOR_TYPE_GRAY,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    
    image_rows = new png_byte*[m_height];
    for(int i=0; i<m_height; ++i)
        image_rows[m_height-i-1] = &m_image_data[m_width*i];

    i_libpng->png_set_rows(png_ptr, info_ptr, image_rows);
    i_libpng->png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    delete[] image_rows;
    image_rows = NULL;

    i_libpng->png_destroy_write_struct(&png_ptr, &info_ptr);
    i_file->fclose(file);
    return true;
}
