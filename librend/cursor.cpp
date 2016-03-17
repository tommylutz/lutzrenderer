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
    if(m_next == m_points.end())
        return false;

    const int x0 = m_first->first;
    const int y0 = m_first->second;

    const int x1 = m_next->first;
    const int y1 = m_next->second;

    m_dx = x1 - x0;
    m_dy = y1 - y0;
    m_x = x0;
    m_y = y0;

    if(abs(m_dx) > abs(m_dy))
    {
        m_axis_to_sweep = &m_x;
        m_axis_increment = (m_dx<0)?-1:1;
        m_axis_target = x1 + m_axis_increment;

        m_error = abs(m_dy) << 1;
        m_error_threshold = abs(m_dx);
        m_error_axis = &m_y;
        m_error_increment = (m_dy<0)?-1:1;
    }
    else
    {
        m_axis_to_sweep = &m_y;
        m_axis_increment = (m_dy<0)?-1:1;
        m_axis_target = y1 + m_axis_increment;

        m_error = abs(m_dx) << 1;
        m_error_threshold = abs(m_dy);
        m_error_axis = &m_x;
        m_error_increment = (m_dx<0)?-1:1;
    }
    return true;
}

bool Cursor::advance(bool * did_y_change, int *x_out, int *y_out)
{
    *did_y_change = false;

    if(!m_bstarted)
    {
        m_bstarted = true;
        m_first = m_points.begin();
        m_next = m_first;
        if(m_next == m_points.end())
            return false;
        m_next++;

        initialize();
        *x_out = m_x;
        *y_out = m_y;
        *did_y_change = true;
        return true;
    }

    const int old_y = m_y;

    m_error_accumulator += m_error;
    if(m_error_threshold &&  //protect against horizontal/vertical line
            m_error_accumulator >= m_error_threshold)
    {
        *m_error_axis += m_error_increment;
        while(m_error_accumulator >= 0)
            m_error_accumulator -= m_error_threshold;
    }

    *m_axis_to_sweep += m_axis_increment;

    *x_out = m_x;
    *y_out = m_y;
    *did_y_change = (old_y!=m_y);

    if(m_x == m_next->first &&
       m_y == m_next->second)
    {
        //Time to advance to next point
        m_next++;
        m_first++;
        if(!initialize())
            return false;
    }
    return true;
}

bool Cursor::done() const
{
    return m_next == m_points.end();
}

bool operator == (const Cursor & c1, const Cursor & c2)
{
    return c1.x() == c2.x() && 
           c1.y() == c2.y();    
}


