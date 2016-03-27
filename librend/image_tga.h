#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <image_interface.h>
#include "external_interfaces/libtga_interface.h"
#include "external_interfaces/file_interface.h"
#include <string>

class TgaImage : public ImageInterface
{
public:
    TgaImage(const char * szFilename,
             libtga_Interface * p_i_libtga);

    TgaImage(int width,
             int height,
             libtga_Interface * p_i_libtga);
    virtual ~TgaImage();
    virtual void set_pixel(int x, int y, const Color& color);
    virtual bool get_pixel(int x, int y, Color& color_out) const;
    bool write(const std::string& strFilename);

    int num_pixels() const;
private:
    //External Interfaces
    libtga_Interface * i_libtga;
    unsigned int * m_image_data;
};



#endif

