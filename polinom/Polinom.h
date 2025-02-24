#pragma once
#include "Monom.h"
#include "Monom.cpp"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // ����������� �� ���������
	Polinom(Monom* p, int size);                    // ����������� � �������� �������

	void addMonom(Monom m);                         // ���������� ������ � �������

	friend std::ostream& operator<<(std::ostream& out, const Polinom& p)
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
};





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
            Node<Monom>* tmp = new Node<Monom>; // ������� ����� ����
            tmp->val = m;                       // ���������� ��� ����� � ����� ����
            tmp->pNext = pCurr;                 // ��������� ����� ���� � �������
            pPrev->pNext = tmp;                 // ��������� ���������� ���� � �����
            return;
        }
    }
}

