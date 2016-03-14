#include "model.h"
#include <string.h>
#include <stdlib.h>
#include <stdexcept>

//===================================================

Vertex::Vertex() :
    m_x(0), m_y(0), m_z(0)
{
}

Vertex::Vertex(double x, double y, double z) :
    m_x(x), m_y(y), m_z(z)
{
}

Vertex::Vertex(const Vertex& other)
{
    Vertex::operator=(other);
}

Vertex& Vertex::operator = (const Vertex& other)
{
    if(this != &other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
    }
    return *this;
}

bool operator == (const Vertex& a, const Vertex &b)
{
    return  a.x() == b.x() &&
            a.y() == b.y() &&
            a.z() == b.z();
}

Vertex Vertex::translate(double xoff, 
                         double yoff, 
                         double zoff, 
                         double scale) const
{
    return Vertex(  (m_x+xoff)*scale,
                    (m_y+yoff)*scale,
                    (m_z+zoff)*scale );
}

//===================================================

Face::Face(const Face& other)
{
    Face::operator=(other);
}

Face& Face::operator=(const Face& other)
{
    if(this != &other)
    {
        m_id1 = other.m_id1;
        m_id2 = other.m_id2;
        m_id3 = other.m_id3;
    }
    return *this;
}

bool operator == (const Face& a, const Face &b)
{
    return  a.id1() == b.id1() &&
            a.id2() == b.id2() &&
            a.id3() == b.id3();
}


//===================================================
Model::Model()
{
}

Model::~Model()
{
}

const Vertex& Model::vertex_at(int idx) const
{
    if(idx-1 >= m_vertexes.size() || idx == 0)
    {
        throw std::invalid_argument("Asked for bad vertex index");
    }
    return m_vertexes[idx-1];
}


void Model::load_vertex(char * buf)
{
    char * saveptr;
    double val[3];

    char * ptr = strtok_r(buf," ",&saveptr);
    for(int i=0; i<3 && ptr; ++i)
    {
        val[i] = atof(ptr);
        if(i == 2)
        {
            m_vertexes.emplace_back(val[0],val[1],val[2]);
            if(m_vertexes.size() == 1)
            {
                m_xrange.first  = val[0];
                m_xrange.second = val[0];
                m_yrange.first  = val[1];
                m_yrange.second = val[1];
                m_zrange.first  = val[2];
                m_zrange.second = val[2];
            }
            else
            {
                if(m_xrange.first  > val[0]) m_xrange.first  = val[0];
                if(m_xrange.second < val[0]) m_xrange.second = val[0];

                if(m_yrange.first  > val[1]) m_yrange.first  = val[1];
                if(m_yrange.second < val[1]) m_yrange.second = val[1];

                if(m_zrange.first  > val[2]) m_zrange.first  = val[2];
                if(m_zrange.second < val[2]) m_zrange.second = val[2];

            }
        }
        ptr = strtok_r(NULL," ",&saveptr);
    }
}

void Model::load_face(char * buf)
{
    char * saveptr;
    int val[3];

    char * ptr = strtok_r(buf," ",&saveptr);
    for(int i=0; i<3 && ptr; ++i)
    {
        val[i] = atoi(ptr); //assume: atoi stops at '/'
        if(i == 2)
            m_faces.emplace_back(val[0],val[1],val[2]);
        ptr = strtok_r(NULL," ",&saveptr);
    }
}

bool Model::load_from_file(const char * szFileName,
                           file_Interface & i_file)
{
    FILE * file = i_file.fopen(szFileName,"rb");
    char buf[512];
    while(i_file.fgets(buf,sizeof(buf),file))
    {
        if(buf[0] == 'v' && buf[1] == ' ')
            load_vertex(&buf[2]);
        else if(buf[0] == 'f' and buf[1] == ' ')
            load_face(&buf[2]);
    }
    i_file.fclose(file);
    return true;
}
