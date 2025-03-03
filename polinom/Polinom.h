#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Monom.h"
#include "List.h"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // ����������� �� ���������
	Polinom(Monom* p, int size);                    // ����������� � �������� �������

	void addMonom(Monom m);                        // ���������� ������ � �������

    Polinom operator+(Polinom& other);          // ��� �������� ���������
    Polinom operator-(Polinom& other);          // ��� ��������� ���������
    Polinom operator*(double constanta);       // ��������� �������� �� ���������
    Polinom operator*(Monom& m);              // ��������� �������� �� �����

    friend std::ostream& operator<<(std::ostream& out, const Polinom& p);


};

// ������� ���� �������� (��� ���������??) �������� � �� ���� ����� - �� ���� �������� �������, ���� ���� �����, ���������� ����� � ����� ��� ������������ 









