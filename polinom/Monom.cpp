#include "Monom.h"

Monom::Monom() : coeff(0), x(0), y(0), z(0) {}

Monom::Monom(double _coeff, int _x, int _y, int _z)
    : coeff(_coeff), x(_x), y(_y), z(_z) {}

void Monom::SetCoeff(double _coeff)
{
    coeff = _coeff;
}

void Monom::SetXYZ(int _x, int _y, int _z)
{
    x = _x;
    y = _y;
    z = _z;
}

bool Monom::operator<(const Monom& m) const
{
    if (x != m.x) return x < m.x;
    if (y != m.y) return y < m.y;
    return z < m.z;
}

bool Monom::operator>(const Monom& m) const
{
    if (x != m.x) return x > m.x;
    if (y != m.y) return y > m.y;
    return z > m.z;
}

bool Monom::operator==(const Monom& m) const
{
    return (x == m.x) && (y == m.y) && (z == m.z);
}

bool Monom::operator!=(const Monom& m) const
{
    return !(*this == m);
}

std::istream& operator>>(std::istream& in, Monom& mon)
{
    std::cout << "������� �����������: ";
    in >> mon.coeff;
    std::cout << "������� ������� x: ";
    in >> mon.x;
    std::cout << "������� ������� y: ";
    in >> mon.y;
    std::cout << "������� ������� z: ";
    in >> mon.z;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Monom& mon)
{
    if (mon.coeff == 0)
    {
        out << "0";
    }
    else
    {
        out << mon.coeff << "x^" << mon.x << "y^" << mon.y << "z^" << mon.z;
    }
    return out;
}
