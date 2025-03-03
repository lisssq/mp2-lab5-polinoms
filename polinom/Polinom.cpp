#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Polinom.h"
#include "Monom.h"
#include "List.h"


std::ostream& operator<<(std::ostream& out, const Polinom& p) 
{
    if (p.pFirst == nullptr)                    // ���� ������� ����, �� ����� �������� "0"
    {
        out << "0";
        return out;
    }

    Node<Monom>* tmp = p.pFirst;                // �������� � ������� ��������
    bool isFirst = true;                          // ����� �� ������� ������ ���� � ������

    while (tmp != nullptr)
    {
        if (!isFirst && tmp->val.coeff > 0)       // ���� ��� �� ������ � �� ������� �����, �� ��������� ���� "+"
            out << " + ";

        out << tmp->val;                        // ������� �������� ������
        tmp = tmp->pNext;                       // ��������� �� ��������� ����
        isFirst = false;                        // ������ ���� ��� ��� �� ������ ����� (���� ������ �������� ���� "+")
    }

    return out;
}



Polinom::Polinom() : List<Monom>() {}           // ����������� �� ��������� (������ ������ �������)

Polinom::Polinom(Monom* p, int size)            // ����������� � �������� �������
{
    for (int i = 0; i < size; i++)
    {
        insLast(p[i]);
    }
}

void Polinom::addMonom(Monom m)                 // ���������� ������ � �������
{
    if (pFirst == nullptr)                      // ���� ������ ����, ��������� � �����
    {
        insLast(m);
        return;
    }
    if (m > pFirst->val)                        // ��������� � ������, ���� �� ������ �������
    {
        insFirst(m);
        return;
    }
    if (m < pLast->val)                         // ��������� � �����, ���� �� ������ ����������
    {
        insLast(m);
        return;
    }

    for (reset(); !isEnd(); goNext())           // �������� � reset() - ������ pCurr �� 1-� ������� ������, ���� �� ��� ��� ���� �� ������ �� �����, ��������� � ����.��������
    {
        if (m == pCurr->val)                    // ���� ����� ����� � ����� �� ��������, ���������� ������������
        {
            pCurr->val.coeff += m.coeff;
            if (pCurr->val.coeff == 0)          // ���� ����������� ���� 0, ������� �����
            {
                delCurr();
            }
            return;
        }
        else if (m > pCurr->val)                // ���� ����� ������ ��������, ��������� ����� ���
        {
            Node<Monom>* tmp = new Node<Monom>(m);; // ������� ����� ����
            tmp->val = m;                       // ���������� ��� ����� � ����� ����
            tmp->pNext = pCurr;                 // ��������� ����� ���� � �������
            pPrev->pNext = tmp;                 // ��������� ���������� ���� � �����
            return;
        }
    }
}



Polinom Polinom::operator+(Polinom& other)
{
    Polinom res(*this);  // �������� ������� �������

    for (other.reset(); !other.isEnd(); other.goNext())
    {
        Monom tmp = other.getCurrent();
        res.addMonom(tmp);  // ��������� ������� �����
    }

    return res;
}

Polinom Polinom::operator-(Polinom& other)
{
    Polinom res(*this);
    for (other.reset(); !other.isEnd(); other.goNext())
    {
        Monom tmp = other.getCurrent();
        tmp.coeff = -tmp.coeff;     //������ ����������� � ������
        res.addMonom(tmp);
    }
    return res;
}


Polinom Polinom::operator*(double constanta)
{
    Polinom res;
    for (reset(); !isEnd(); goNext())
    {
        Monom tmp = getCurrent();
        tmp.coeff *= constanta;
        res.addMonom(tmp);
    }
    return res;
}


Polinom Polinom:: operator*(Monom& m)
{
    Polinom res;
    for (reset(); !isEnd(); goNext())
    {
        Monom tmp = getCurrent();
        tmp.coeff *= m.coeff;
        tmp.x += m.x;
        tmp.y += m.y;
        tmp.z += m.z;
        res.addMonom(tmp);
    }
    return res;
}