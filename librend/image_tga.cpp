#include "image_tga.h"
#include "external_interfaces/libtga_interface.h"
#include "external_interfaces/file_interface.h"
#include <stdexcept>
#include <string.h>

TgaImage::TgaImage(
             int width,
             int height,
             libtga_Interface *p_i_libtga) :
    ImageInterface(width, height),
    i_libtga(p_i_libtga)
{
    m_image_data = new unsigned int[width*height];
    for(int i=0; i<width*height; ++i)
        m_image_data[i] = 0;
}

TgaImage::TgaImage(const char * szFilename,
                libtga_Interface *p_i_libtga) :
    i_libtga(p_i_libtga),
    m_image_data(NULL)
{
    TGA * tga = i_libtga->TGAOpen(szFilename, "rb");

    if(!tga)
        return; //TODO: Throw something?

    TGAData tgaData;
    memset(&tgaData,0,sizeof(tgaData));
    tgaData.flags |= TGA_RGB;
    tgaData.flags |= TGA_IMAGE_ID;
    tgaData.flags |= TGA_COLOR_MAP;
    tgaData.flags |= TGA_IMAGE_DATA;

    int rc = i_libtga->TGAReadImage(tga,&tgaData);
    
    if(rc == TGA_OK)
    {
        /*printf("READ THE TGA IMAGE!!\n");
        printf("image id: %p\n",tgaData.img_id);
        printf("cmap: %p\n",tgaData.cmap);
        printf("img_data: %p\n",tgaData.img_data);
        printf("depth: %d\n",tga->hdr.depth);
        printf("width: %d\n",tga->hdr.width);
        printf("height: %d\n",tga->hdr.height);*/
        m_image_data = new unsigned int [tga->hdr.width * tga->hdr.height];
    
        ImageInterface::init(tga->hdr.width,
                             tga->hdr.height);

        for(int pxl=0; pxl< tga->hdr.width*tga->hdr.height; ++pxl)
        {
            int idx = pxl*3;
            Color color = 0xFF000000;
            color |= tgaData.img_data[idx];
            color |= tgaData.img_data[idx+1]<<8;
            color |= tgaData.img_data[idx+2]<<16;

            const int x = pxl%tga->hdr.width;
            const int y = pxl/tga->hdr.height;
            set_pixel(x,y,color);
            /*printf("At (%d,%d), pixel is %.8x\n",
                    x, y, color);
            Color clr;
            if(get_pixel(x,y,clr))
                printf("Got pixel %.8x\n",clr);
            else
                printf("Failed to get pixel\n");*/
        }

    }
    else
    {
        //TODO: Throw something?
    }

    if(tgaData.img_id)  free(tgaData.img_id);
    if(tgaData.cmap)    free(tgaData.cmap);
    if(tgaData.img_data)free(tgaData.img_data);
    i_libtga->TGAClose(tga);
}
        

TgaImage::~TgaImage()
{
    if(m_image_data) delete[] m_image_data;
}

void TgaImage::set_pixel(int x, int y, const Color& color)
{
    assert(m_image_data);
    if(x>=0 && x < m_width &&
       y>=0 && y < m_height)
    {
        m_image_data[x+y*m_width] = color;
    }
}

bool TgaImage::get_pixel(int x, int y, Color& color_out) const
{
    assert(m_image_data);
    if(x < m_width and y < m_height)
    {
        color_out = m_image_data[x+y*m_height];
        return true;
    }
    return false;
}

bool TgaImage::write(const std::string& strFilename)
{
    return false; //Not implemented for now
}




