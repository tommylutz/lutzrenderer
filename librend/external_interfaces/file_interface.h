#ifndef _FILE_INTERFACE_H_
#define _FILE_INTERFACE_H_
#include <stdio.h>


class file_Interface
{
public:
    virtual ~file_Interface() { }
    virtual FILE * fopen(const char * fname,
                         const char * mode)
    {
        return ::fopen(fname,mode);
    }

    virtual void fclose(FILE * file)
    {
        ::fclose(file);
    }

    virtual char * fgets(char * buf, int num, FILE * file)
    {
        return ::fgets(buf,num,file);
    }
};



#endif

