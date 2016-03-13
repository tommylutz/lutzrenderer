#ifndef _MODEL_H_
#define _MODEL_H_

#include <file_interface.h>

class Model
{
public:
    Model();
    ~Model();
    bool load_from_file(const char * szFileName,
                        file_Interface & i_file);
};


#endif

