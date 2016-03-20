#ifndef _MODEL_H_
#define _MODEL_H_

#include <file_interface.h>
#include <vector>
#include <vec3.h>

class Face
{
public:
    Face(int id1, int id2, int id3) : m_id1(id1), m_id2(id2), m_id3(id3) {}
    Face(const Face& other);
    Face& operator=(const Face& other);
    inline int id1() const { return m_id1; }
    inline int id2() const { return m_id2; }
    inline int id3() const { return m_id3; }
private:
    int m_id1, m_id2, m_id3;
};
bool operator == (const Face& a, const Face &b);

class Model
{
public:
    Model();
    ~Model();
    bool load_from_file(const char * szFileName,
                        file_Interface & i_file);
    const Vec3f& vertex_at(int idx) const;
    inline const Face& face_at(int idx) { return m_faces[idx]; }
    inline int num_vertexes() const { return m_vertexes.size(); }
    inline int num_faces() const { return m_faces.size(); }
    inline const std::pair<double, double>& xrange() const { return m_xrange; }
    inline const std::pair<double, double>& yrange() const { return m_yrange; }
    inline const std::pair<double, double>& zrange() const { return m_zrange; }
private:
    void load_face(char * buf);
    void load_vertex(char * buf);
    std::vector<Vec3f> m_vertexes;
    std::vector<Face> m_faces;

    std::pair<double, double> m_xrange;
    std::pair<double, double> m_yrange;
    std::pair<double, double> m_zrange;
    Vec3f m_dumbvertex;
};


#endif

