#ifndef _MOCK_FILE_INTERFACE_H_
#define _MOCK_FILE_INTERFACE_H_

#include "file_interface.h"
#include "<gmock/gmock.h>"

class Mockfile_Interface : public file_Interface {
 public:
  MOCK_METHOD2(fopen,
      FILE*(const char * fname, const char * mode));
  MOCK_METHOD1(fclose,
      void(FILE * file));
};

#endif

