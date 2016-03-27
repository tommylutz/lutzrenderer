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
        printf("READ TEH TGA IMAGE!!\n");
        printf("image id: %p\n",tgaData.img_id);
        printf("cmap: %p\n",tgaData.cmap);
        printf("img_data: %p\n",tgaData.img_data);
        printf("depth: %d\n",tga->hdr.depth);
        printf("width: %d\n",tga->hdr.width);
        printf("height: %d\n",tga->hdr.height);
    
        ImageInterface::init(tga->hdr.width,
                             tga->hdr.height);

        for(int i=0; i< 64; ++i)
        {
            printf("%.2x ",tgaData.img_data[i]);
            if( (i+1)%8 == 0 )
                printf("  ");
            if( (i+1)%32 == 0)
                printf("\n");
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
    if(x>=0 && x < m_width &&
       y>=0 && y < m_height)
    {
        m_image_data[x+y*m_width] = color;
    }
}

bool TgaImage::get_pixel(int x, int y, Color& color_out) const
{
    return false;
}

bool TgaImage::write(const std::string& strFilename)
{
    return false; //Not implemented for now
}




