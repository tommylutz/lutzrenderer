#ifndef _PNG_IMAGE_H_
#define _PNG_IMAGE_H_

#include <image_interface.h>
#include "external_interfaces/libpng_interface.h"
#include "external_interfaces/file_interface.h"
#include <string>

class PngImage : public ImageInterface
{
public:
    PngImage(int width,
             int height,
             libpng_Interface * p_i_libpng,
             file_Interface * p_i_file);
    virtual ~PngImage();
    virtual void set_pixel(int x, int y, const Color& color);
    bool write(const std::string& strFilename);

    int num_pixels() const;
private:
    png_structp m_png_write_ptr;
    png_infop m_png_info_ptr;

    //External Interfaces
    libpng_Interface * i_libpng;
    file_Interface * i_file;
    unsigned int * m_image_data;
};



#endif

