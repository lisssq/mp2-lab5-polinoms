#pragma once
#include "Monom.h"
#include "Monom.cpp"


class Polynom :public List<Monom>
{
public:

	Polynom() : List<Monom>() {}  // ����������� �� ��������� (������ ������ �������)

	friend std::ostream& operator<<(std::ostream& out, const Polynom& p)
	{
		if (p.pFirst == nullptr) {
			out << "0";
			return out;
		}

		Node<Monom>* temp = p.pFirst;
		bool first = true; // ����� �� ������� ������ ���� � ������

		while (temp != nullptr)
		{
			if (!first && temp->val.coeff > 0)
				out << " + ";

			out << temp->val;
			temp = temp->pNext;
			first = false;
		}

		return out;
	}

	Polynom(Monom* p, int size)
	{
		for (int i = 0; i < size; i++)
		{
			insLast(p[i]);
		}
	}



	void addMonom(Monom m)
	{
		if (pFirst == nullptr)		// ���� ������ ����, �� ������ ��������� �����
		{
			insLast(m);
			return;
		}
		if (m > pFirst->val)		// ���� ����� ������ �������, �� ��������� ��� � ������ ������
		{
			insFirst(m);
			return;
		}
		if (m < pLast->val)			// ���� ����� ������ ����������, ��������� � ����� ������
		{
			insLast(m);
			return;
		}

		for (reset(); !isEnd(); goNext())
		{
			if (m == pCurr->val) // ���� ����� ����� � ����� �� ��������, ���������� ������������
			{
				pCurr->val.coeff += m.coeff;
				if (pCurr->val.coeff == 0) // ���� ����������� ���� 0, ������� �����
				{
					delCurr();
				}
				return;
			}
			else if (m > pCurr->val) // ���� ����� ������ ��������, ��������� ����� ���
			{
				Node<Monom>* tmp = new Node<Monom>;
				tmp->val = m;
				tmp->pNext = pCurr;
				pPrev->pNext = tmp;
				return;
			}
		}
	}


};