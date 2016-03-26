#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <image_interface.h>
#include "external_interfaces/libtga_interface.h"
#include "external_interfaces/file_interface.h"
#include <string>

class TgaImage : public ImageInterface
{
public:
    TgaImage(int width,
             int height,
             libtga_Interface * p_i_libtga,
             file_Interface * p_i_file);
    virtual ~TgaImage();
    virtual void set_pixel(int x, int y, const Color& color);
    virtual bool get_pixel(int x, int y, Color& color_out) const;
    bool write(const std::string& strFilename);

    int num_pixels() const;
private:
    //External Interfaces
    libtga_Interface * i_libtga;
    file_Interface * i_file;
    unsigned int * m_image_data;
};



#endif

