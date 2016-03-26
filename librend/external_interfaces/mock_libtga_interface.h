#ifndef _MOCK_LIBTGA_INTERFACE_H_
#define _MOCK_LIBTGA_INTERFACE_H_

#include "libtga_interface.h"

class Mocklibtga_Interface : public libtga_Interface {
 public:
  MOCK_METHOD2(TGAOpen,
      TGA*(char *name, char *mode));
  MOCK_METHOD1(TGAOpenFd,
      TGA*(FILE *fd));
  MOCK_METHOD1(TGAReadHeader,
      int(TGA *tga));
  MOCK_METHOD2(TGAReadImageId,
      int(TGA *tga, tbyte **id));
  MOCK_METHOD3(TGAReadColorMap,
      int(TGA *tga, tbyte **cmap, tuint32 flags));
  MOCK_METHOD5(TGAReadScanlines,
      size_t(TGA *tga, tbyte *buf, size_t sln, size_t n, tuint32 flags));
  MOCK_METHOD2(TGAReadImage,
      int(TGA *tga, TGAData *data));
  MOCK_METHOD1(TGAWriteHeader,
      int(TGA *tga));
  MOCK_METHOD2(TGAWriteImageId,
      int(TGA *tga, const tbyte *id));
  MOCK_METHOD3(TGAWriteColorMap,
      int(TGA *tga, tbyte *cmap, tuint32 flags));
  MOCK_METHOD5(TGAWriteScanlines,
      size_t(TGA *tga, tbyte *buf, size_t sln, size_t n, tuint32 flags));
  MOCK_METHOD2(TGAWriteImage,
      int(TGA *tga, TGAData *data));
  MOCK_METHOD1(TGAStrError,
      const char*(tuint8 code));
  MOCK_METHOD3(__TGASeek,
      tlong(TGA *tga, tlong off, int whence));
  MOCK_METHOD3(__TGAbgr2rgb,
      void(tbyte *data, size_t size, size_t bytes));
  MOCK_METHOD1(TGAClose,
      void(TGA *tga));
};

#endif

