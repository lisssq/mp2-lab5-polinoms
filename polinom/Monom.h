#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "List.h"

struct Monom
{
    double coeff;
    int x, y, z;

public:
    Monom();                              // oбъявление конструктора по умолчанию
    Monom(double _coeff, int x, int y, int z); // oбъявление конструктора с параметрами

    void SetCoeff(double _coeff);
    void SetXYZ(int _x, int _y, int _z);

    bool operator<(const Monom& m) const;
    bool operator>(const Monom& m) const;
    bool operator==(const Monom& m) const;
    bool operator!=(const Monom& m) const;

    friend std::ostream& operator<<(std::ostream& out, const Monom& mon);
};

std::istream& operator>>(std::istream& in, Monom& mon);
