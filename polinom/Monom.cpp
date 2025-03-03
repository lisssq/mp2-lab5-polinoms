#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Monom.h"


 
std::ostream& operator<<(std::ostream& out, const Monom& mon)
{
	out << mon.coeff << "x^" << mon.x << "y^" << mon.y << "z^" << mon.z;
	return out;
}


Monom::Monom() : coeff(0), x(0), y(0), z(0) {}			// конструктор по умолчанию


Monom::Monom(double _coeff, int _x, int _y, int _z)		// конструктор с параметрами
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


bool Monom::operator<(const Monom& m) const				// операторы сравнения (лексикографический порядок)
{
	if (x != m.x)
	{
		return x < m.x;
	}
	if (y != m.y)
	{
		return y < m.y;
	}
	return z < m.z;
}

bool Monom::operator>(const Monom& m) const
{
	if (x != m.x)
	{
		return x > m.x;
	}
	if (y != m.y)
	{
		return y > m.y;
	}
	return z > m.z;
}

bool Monom::operator==(const Monom& m) const
{
	return (x == m.x) && (y == m.y) && (z == m.z);
}

