#ifndef _TGA_INTERFACE_H_
#define _TGA_INTERFACE_H_

#include <tga.h>

class libtga_Interface
{
public:
    virtual ~libtga_Interface() { }
    virtual TGA* TGAOpen (const char *name, const char *mode)
    {
        return ::TGAOpen(name,mode);
    }
    
    virtual TGA* TGAOpenFd (FILE *fd)
    {
        return ::TGAOpenFd(fd);
    }
    
    virtual int TGAReadHeader (TGA *tga)
    {
        return ::TGAReadHeader(tga);
    }

    virtual int TGAReadImageId (TGA *tga, tbyte **id)
    {
        return ::TGAReadImageId(tga,id);
    }
    
    virtual int TGAReadColorMap (TGA *tga, tbyte **cmap, tuint32 flags)
    {
        return ::TGAReadColorMap(tga, cmap, flags);
    }

    virtual size_t TGAReadScanlines (TGA *tga, 
                                     tbyte *buf, 
                                     size_t sln, 
                                     size_t n,
                                     tuint32 flags) 
    {
        return ::TGAReadScanlines(tga,buf,sln,n,flags);
    }
    
    virtual int TGAReadImage (TGA *tga, TGAData *data)
    {
        return ::TGAReadImage(tga,data);
    }
    
    virtual int TGAWriteHeader (TGA *tga)
    {
        return ::TGAWriteHeader(tga);
    }
    
    virtual int TGAWriteImageId (TGA *tga, const tbyte *id)
    {
        return ::TGAWriteImageId(tga,id);
    }
    
    virtual int TGAWriteColorMap (TGA *tga, tbyte *cmap, tuint32 flags)
    {
        return ::TGAWriteColorMap(tga,cmap,flags);
    }

    virtual size_t TGAWriteScanlines (TGA *tga, tbyte *buf, size_t sln, size_t n, tuint32 flags)
    {
        return ::TGAWriteScanlines(tga,buf,sln,n,flags);
    }

    virtual int TGAWriteImage (TGA *tga, TGAData *data)
    {
        return ::TGAWriteImage(tga,data);
    }

    virtual const char* TGAStrError (tuint8 code)
    {
        return ::TGAStrError(code);
    }

    virtual tlong __TGASeek (TGA *tga, tlong off, int whence)
    {
        return ::__TGASeek(tga,off,whence);
    }
    
    virtual void __TGAbgr2rgb (tbyte *data, size_t size, size_t bytes)
    {
        return ::__TGAbgr2rgb(data,size,bytes);
    }

    virtual void TGAClose (TGA *tga)
    {
        return ::TGAClose(tga);
    }
};


#endif

