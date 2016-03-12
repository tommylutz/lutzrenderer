#ifndef _MOCK_LIBPNG_INTERFACE_H_
#define _MOCK_LIBPNG_INTERFACE_H_

#include "libpng_interface.h"
#include "<gmock/gmock.h>"

class Mocklibpng_Interface : public libpng_Interface {
 public:
  MOCK_METHOD4(png_create_write_struct,
      png_structp(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn));
  MOCK_METHOD2(png_destroy_write_struct,
      void(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr));
  MOCK_METHOD1(png_create_info_struct,
      png_infop(png_structp png_ptr));
  MOCK_METHOD2(fopen,
      FILE*(const char * szFilename, const char * szMode));
  MOCK_METHOD1(fclose,
      void(FILE *file));
};

#endif

