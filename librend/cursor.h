#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <list>
#include <utility>

class Cursor
{
public:
    Cursor();
    void add_point(int x, int y);
    bool advance();
    int x() const;
    int y() const;
    bool done() const;
private:
    bool initialize();
    void setup_line_drawing_params();

    std::list<std::pair<int,int> > m_points;
    std::list<std::pair<int,int> >::const_iterator m_start;
    std::list<std::pair<int,int> >::const_iterator m_end;

    bool m_bstarted;
    int m_x, m_y;
    int m_dx, m_dy;
    int m_dx2, m_dy2;
    int m_x_sign, m_y_sign;
    int m_error;
    int m_x1, m_y1;
};

bool operator == (const Cursor & c1, const Cursor & c2);


#endif

