#include "../inc/tacka.hpp"

Tacka::Tacka()
{

}

Tacka::Tacka(double x, double y)
    : m_x(x)
    , m_y(y)
{

}

Tacka::~Tacka()
{

}

double Tacka::get_x() const
{
    return m_x;
}

double Tacka::get_y() const
{
    return m_y;
}
