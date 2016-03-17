#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <list>
#include <utility>

class Cursor
{
public:
    Cursor();
    void add_point(int x, int y);
    bool advance(bool * did_y_change, int *x_out, int *y_out);
    int x() const;
    int y() const;
    bool done() const;
private:
    bool initialize();

    std::list<std::pair<int,int> > m_points;
    std::list<std::pair<int,int> >::const_iterator m_first;
    std::list<std::pair<int,int> >::const_iterator m_next;
    bool m_bstarted;
    int m_x, m_y;

    int m_dx, m_dy;
    int * m_axis_to_sweep;
    int m_axis_increment;
    int m_axis_target;
    int m_error;
    int m_error_accumulator;
    int *m_error_axis;
    int m_error_increment;
    int m_error_threshold;
};

bool operator == (const Cursor & c1, const Cursor & c2);


#endif

