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
        return ::png_destroy_write_struct(png_ptr_ptr, info_ptr_ptr);
    }

    virtual png_infop png_create_info_struct(png_structp png_ptr)
    {
        return ::png_create_info_struct(png_ptr);
    }

    virtual FILE * fopen(const char * szFilename, const char * szMode)
    {   
        return ::fopen(szFilename, szMode);
    }

    virtual void fclose(FILE *file)
    {
        ::fclose(file);
    }
};


#endif

