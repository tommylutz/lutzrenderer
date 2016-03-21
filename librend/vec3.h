#ifndef __VEC3_H_
#define __VEC3_H_

#include <math.h>
#include <iostream>

template<typename T>
class Vec3
{
public:
    Vec3() :
        m_i(0),
        m_j(0),
        m_k(0)
    {
    }

    Vec3(const T& i, const T& j, const T& k) :
        m_i(i),
        m_j(j),
        m_k(k)
    {
    }

    inline T i() const { return m_i; }
    inline T j() const { return m_j; }
    inline T k() const { return m_k; }
    inline T x() const { return m_i; }
    inline T y() const { return m_j; }
    inline T z() const { return m_k; }

    Vec3 operator+(const Vec3& other) const
    {
        return Vec3<T>(m_i + other.m_i,
                       m_j + other.m_j,
                       m_k + other.m_k);
    }

    Vec3 operator-(const Vec3& other) const
    {
        return Vec3<T>(m_i - other.m_i,
                       m_j - other.m_j,
                       m_k - other.m_k);
    }

    Vec3 cross_product(const Vec3& b) const
    {
        return Vec3<T>( m_j * b.m_k - m_k * b.m_j,
                        m_k * b.m_i - m_i * b.m_k,
                        m_i * b.m_j - m_j * b.m_i );
    }
    Vec3 operator^(const Vec3& b) const
    {
        return cross_product(b);
    }

    T dot_product(const Vec3& b) const
    {
        return  m_i * b.m_i +
                m_j * b.m_j +
                m_k * b.m_k;
    }
    T operator*(const Vec3& b) const
    {
        return dot_product(b);
    }

    double magnitude() const
    {
        return sqrt(((double)(m_i*m_i))+
                    ((double)(m_j*m_j))+
                    ((double)(m_k*m_k)));
    }

    Vec3 operator/(double d) const
    {
        return Vec3(m_i/d,
                    m_j/d,
                    m_k/d);
    }

    Vec3<double> normalize() const
    {
        return (*this) / this->magnitude();

    }

private:
    T m_i, m_j, m_k;
};

template <typename T>
bool operator==(const Vec3<T>& vec1,
                const Vec3<T>& vec2)
{
    return vec1.i() == vec2.i() &&
           vec1.j() == vec2.j() &&
           vec1.k() == vec2.k();
}

template <typename T>
Vec3<T> operator*(const Vec3<T>& vec, double d)
{
    return Vec3<T>(vec.i()*d,
                   vec.j()*d,
                   vec.k()*d);
}

template <typename T>
std::ostream& operator << (std::ostream& strm, const Vec3<T> & vec)
{
    strm << "(" << vec.x() << "," << vec.y() << "," << vec.z() << ")";
    return strm;
}

typedef Vec3<double> Vec3f;





#endif

