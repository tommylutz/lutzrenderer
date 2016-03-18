#include "cursor.h"
#include <math.h>
#include <stdlib.h>

Cursor::Cursor() :
    m_bstarted(false),
    m_x(0),
    m_y(0)
{
}

int Cursor::x() const
{
    return m_x;
}

int Cursor::y() const
{
    return m_y;
}

void Cursor::add_point(int x, int y)
{
    m_points.push_back(std::make_pair(x,y));
}

bool Cursor::initialize()
{
    return true;
}

void Cursor::setup_line_drawing_params()
{
    //Requires: m_start and m_end are valid iterators, not pointing to the end of the list
    m_x = m_start->first;
    m_y = m_start->second;
    m_x1 = m_end->first;
    m_y1 = m_end->second;
    m_error = 0;
    m_dx = abs(m_x1 - m_x);
    m_dy = abs(m_y1 - m_y);
    m_dx2 = m_dx*2;
    m_dy2 = m_dy*2;
    m_x_sign = (m_x1 >= m_x) ? 1 : -1;
    m_y_sign = (m_y1 >= m_y) ? 1 : -1;
}

bool Cursor::done() const
{
    return m_end == m_points.end();
}

bool Cursor::advance()
{
    if(!m_bstarted)
    {
        m_bstarted = true;
        if(m_points.empty())
            return false;
        
        m_start = m_points.begin();
        m_end = m_start;
        ++m_end;
    
        //Take care of case where only 1 point was added
        if(m_end == m_points.end())
        {
            m_x = m_start->first;
            m_y = m_start->second;
            return true;
        }

        setup_line_drawing_params();
        return true;
    }

    if(m_end == m_points.end())
        return false;

    while(m_y == m_y1 && m_x == m_x1)
    {
        ++m_start;
        ++m_end;
        if(m_end != m_points.end())
            setup_line_drawing_params();
        else
            return false; //No more lines to draw
    }
    
    if(m_dx > m_dy)
    {
        m_x += m_x_sign;
        m_error += m_dy2;
        if(m_error >= m_dx)
        {
            m_y += m_y_sign;
            m_error -= m_dx2;
        }
    }
    else
    {
        m_y += m_y_sign;
        m_error += m_dx2;
        if(m_error >= m_dy)
        {
            m_x += m_x_sign;
            m_error -= m_dy2;
        }
    }

    return true;
}

bool operator == (const Cursor & c1, const Cursor & c2)
{
    return c1.x() == c2.x() && 
           c1.y() == c2.y();    
}


