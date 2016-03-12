
#include "image_png.h"
#include "external_interfaces/libpng_interface.h"
#include "external_interfaces/file_interface.h"
#include <stdexcept>

PngImage::PngImage(const std::string& strFileName,
             int width,
             int height,
             libpng_Interface *p_i_libpng,
             file_Interface * p_i_file) :
    m_width(width),
    m_height(height),
    m_strFileName(strFileName),
    m_file(NULL),
    m_png_write_ptr(NULL),
    m_png_info_ptr(NULL),
    i_libpng(p_i_libpng),
    i_file(p_i_file)
{
    m_file = i_file->fopen(m_strFileName.c_str(),"wb");
    if(!m_file)
        throw std::invalid_argument(
            std::string("Unable to open filename ")+m_strFileName);

    /*m_png_write_ptr = 
        i_libpng->png_create_write_struct(
            PNG_LIBPNG_VER_STRING,
            (png_voidp)user_error_ptr,
            user_error_fn,
             user_warning_fn); */

    if(!m_png_write_ptr)
        throw std::bad_alloc();
    
    m_png_info_ptr =
        i_libpng->png_create_info_struct(m_png_write_ptr);

    if(!m_png_info_ptr)
    {
        i_libpng->png_destroy_write_struct(&m_png_write_ptr,
                                 (png_infopp)NULL);
        throw std::bad_alloc();
    }
}

PngImage::~PngImage()
{
    if(m_file)
    {
        i_file->fclose(m_file);
        m_file = NULL;
    }
}

