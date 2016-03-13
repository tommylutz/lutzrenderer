#include "model.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::load_from_file(const char * szFileName,
                           file_Interface & i_file)
{
    FILE * file = i_file.fopen(szFileName,"rb");
    char buf[512];
    while(i_file.fgets(buf,sizeof(buf),file))
    {
        printf("Read line: [%s]\n",buf);
    }
    i_file.fclose(file);
    return false;
}
