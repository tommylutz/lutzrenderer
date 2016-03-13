#ifndef _MOCK_LIBPNG_INTERFACE_H_
#define _MOCK_LIBPNG_INTERFACE_H_

#include "libpng_interface.h"

class Mocklibpng_Interface : public libpng_Interface {
 public:
  MOCK_METHOD4(png_create_write_struct,
      png_structp(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn));
  MOCK_METHOD2(png_destroy_write_struct,
      void(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr));
  MOCK_METHOD1(png_create_info_struct,
      png_infop(png_structp png_ptr));
  MOCK_METHOD2(png_init_io,
      void(png_structp png_ptr, png_FILE_p fp));
  MOCK_METHOD9(png_set_IHDR,
      void(png_structp png_ptr, png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method));
  MOCK_METHOD4(png_write_png,
      void(png_structp png_ptr, png_infop info_ptr, int transforms, png_voidp params));
  MOCK_METHOD2(png_write_end,
      void(png_structp png_ptr, png_infop info_ptr));
  MOCK_METHOD2(png_write_image,
      void(png_structp png_ptr, png_bytepp image));
  MOCK_METHOD1(png_jmp_buf,
      jmp_buf*(png_structp png_ptr));
  MOCK_METHOD3(png_set_rows,
      void(png_structp png_ptr, png_infop info_ptr, png_bytepp row_pointers));
};

#endif

