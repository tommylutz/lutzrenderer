#ifndef _PNG_INTERFACE_H_
#define _PNG_INTERFACE_H_

#include <png.h>

class libpng_Interface
{
public:
    virtual ~libpng_Interface() { }
    virtual png_structp png_create_write_struct(
                            png_const_charp user_png_ver,
                            png_voidp error_ptr,
                            png_error_ptr error_fn,
                            png_error_ptr warn_fn)
    {
        return ::png_create_write_struct(user_png_ver,
                                  error_ptr,
                                  error_fn,
                                  warn_fn);
    }

    virtual void png_destroy_write_struct(png_structpp png_ptr_ptr, 
                                          png_infopp info_ptr_ptr)
    {
        ::png_destroy_write_struct(png_ptr_ptr, info_ptr_ptr);
    }

    virtual png_infop png_create_info_struct(png_structp png_ptr)
    {
        return ::png_create_info_struct(png_ptr);
    }

    virtual void png_init_io(png_structp png_ptr, png_FILE_p fp)
    {
        ::png_init_io(png_ptr, fp);
    }
    
    virtual void png_set_IHDR(png_structp png_ptr,
               png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth,
               int color_type, int interlace_method, int compression_method,
               int filter_method)
    {
        ::png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
                              interlace_method, compression_method, filter_method);
    }

    virtual void png_write_png(png_structp png_ptr,
                        png_infop info_ptr,
                        int transforms,
                        png_voidp params)
    {
        ::png_write_png(png_ptr, info_ptr, transforms, params);
    }

    virtual void png_write_end(png_structp png_ptr, png_infop info_ptr)
    {
        ::png_write_end(png_ptr, info_ptr);
    }

    virtual void png_write_image(png_structp png_ptr, png_bytepp image)
    {
        ::png_write_image(png_ptr, image);
    }

    virtual jmp_buf* png_jmp_buf(png_structp png_ptr)
    {   
        //Note: png_jmpbuf is a macro that accesses a member of png_ptr struct
        return &(png_jmpbuf(png_ptr));
    }


};


#endif

