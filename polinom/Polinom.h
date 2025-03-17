#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <string>
#include <sstream> // ��������� include ��� std::ostringstream
#include <vector>
#include "Monom.h"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // ����������� �� ���������
	Polinom(const Polinom& p);						// ����������� �����������
	Polinom(Monom* p, int size);                    // ����������� � �������� �������
	~Polinom();

	void addMonom(Monom m);							// ���������� ������ � �������

	Polinom operator+(Polinom& other);				// ��� �������� ���������
	Polinom operator-(Polinom& other);				// ��� ��������� ���������
	Polinom operator*(double constanta);		    // ��������� �������� �� ���������
	Polinom operator*(Monom& m);					// ��������� �������� �� �����
	bool operator==(Polinom& other);

	Polinom& operator+=(Polinom& pol);
	Polinom& operator-=(Polinom& pol);


	friend std::ostream& operator<<(std::ostream& out, const Polinom& p)
	{
		if (p.pFirst == nullptr) // ���� ������� ����, ������� ����
		{
			out << "0";
			return out;
		}

		Node<Monom>* tmp = p.pFirst;
		bool isFirst = true;
		bool hasNonZero = false; // ���� ��� ��������, ���� �� ��������� ������

		while (tmp != nullptr)
		{
			double coeff = tmp->val.coeff;

			if (coeff != 0) // ���������, ��� ����������� �� ����� ����
			{
				hasNonZero = true; // ������������� ����, ���� ����� ��������� �����

				if (isFirst)
				{
					if (coeff < 0)
					{
						out << "-";
						coeff = -coeff;
					}
				}
				else
				{
					if (coeff > 0)
					{
						out << " + ";
					}
					else if (coeff < 0)
					{
						out << " - ";
						coeff = -coeff;
					}
				}

				out << coeff; // ������� �����������

				// ������� ������� x, y, z
				out << "x^" << tmp->val.x;
				out << "y^" << tmp->val.y;
				out << "z^" << tmp->val.z;
			}

			tmp = tmp->pNext;
			isFirst = false;
		}

		if (!hasNonZero) // ���� �� ���� ��������� �������, ������� "0"
		{
			out << "0";
		}

		return out;
	}
};


std::istream& operator>>(std::istream& in, Polinom& pol)		// ���� ������� � �������
{
	int numMonoms;
	std::cout << "������� ���������� ������� � ��������: ";
	in >> numMonoms;

	for (int i = 0; i < numMonoms; ++i) 
	{
		Monom mon;
		in >> mon;
		pol.addMonom(mon);
	}
	return in;
}


std::string toStr(const Polinom& p)
{
	std::ostringstream oss;
	oss << p;				// ����� �������� � ostringstream
	return oss.str();
}



Polinom::Polinom() {};

Polinom::Polinom(const Polinom& p) : List<Monom>(p)
{
}


Polinom::Polinom(Monom* p, int size)            // ����������� � �������� �������
{
	pFirst = pLast = nullptr;
	sz = 0;
	for (int i = 0; i < size; i++)
	{
		addMonom(p[i]);
	}
}

Polinom::~Polinom()
{
}

void Polinom::addMonom(Monom m)                 // ���������� ������ � �������
{
	if (pFirst == nullptr)                      // ���� ������ ����, ��������� � �����
	{
		insLast(m);
		return;
	}

	reset();									// ������������ � ������ ������

	while (!isEnd() && pCurr->val > m)			// ���� �� ����� ������ � ������� ����� ������ ������������
	{	
		goNext();								// ���� ������
	}

	if (!isEnd() && pCurr->val == m)			// ���� ������� � ����������� ����� �����, �� 
	{
		pCurr->val.coeff += m.coeff;			// ���������� ������������

		if (pCurr->val.coeff == 0)				// ���� �� ��������� - �������
		{
			delCurr();
		}
	}
	else										// ���� ����� ������ ��������, ��������� ����� ���
	{
		Node<Monom>* tmp = new Node<Monom>{ m, pCurr }; // ������� ����� ����

		if (pPrev == nullptr)					// ���� ����� ������ ����� ������
		{
			pFirst = tmp;
		}
		else 
		{
			pPrev->pNext = tmp;					// ����� ��������� ���������� ������� � �����
		}

		if (pCurr == nullptr)					// ���� ����� ����� ������ ���� ���������
		{
			pLast = tmp;
		}
		sz++;
	}
}


Polinom Polinom::operator+(Polinom& other)
{
	Polinom res(*this);						// �������� ������� �������

	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();		// �������� ������� �����
		res.addMonom(tmp);					// ��������� ������� ����� � ���������
	}
	return res;
}

Polinom Polinom::operator-(Polinom& other)
{
	Polinom res(*this);
	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		tmp.coeff = -tmp.coeff;				// ������ ����������� � ������
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

bool Polinom :: operator==(Polinom& other)
{
	if (sz != other.sz)							// ���� ������� ��������� �� �����, �� ���� �������� �������� ����
	{
		return false;
	}
	reset();									// ���� � ������ ����� ���������
	other.reset();
	while (!isEnd())
	{
		if (getCurrent() != other.getCurrent())
		{
			return false;
		}
		goNext();
		other.goNext();
	}
	return true;
}


Polinom& Polinom:: operator+=(Polinom& pol) {
	Polinom res;
	this->reset();								// ���������� ��������� ����� ��������� � ������
	pol.reset();

	while (!this->isEnd() || !pol.isEnd())		// ���� �����-�� ������� �� ��������
	{
		if (this->isEnd())						// ���� �������� ������� ��������
		{
			if (!pol.isEnd())					// �� ������ ��� ����� ������
			{
				res.addMonom(pol.getCurrent());	// �� ������ ��������� �� � �������������� �������
				pol.goNext();
			}
		}
		else if (pol.isEnd())					// ���� �� ������ ������� ��������, �� ������ �� �� �����, ������ � �����
		{
			res.addMonom(this->getCurrent());
			this->goNext();
		}
		else if (pol.getCurrent() > this->getCurrent())	// ���� ������� ������ �� 2 �������� ������, �� ��������� ��� � ���������
		{
			res.addMonom(pol.getCurrent());
			pol.goNext();								// ���� � ����.������ 2 ��������, ��������� � �������� - �������
		}
		else if (this->getCurrent() > pol.getCurrent()) // ���� ������ - ��������� �� 1
		{
			res.addMonom(this->getCurrent());
			this->goNext();								// � ���� � ����. � ������� ��������, ��������� �� 2 �� ��������
		}
		else											// ���� ������� ����������
		{
			Monom sum = this->getCurrent();				// �� ���������� �����.��� �������
			sum.coeff += pol.getCurrent().coeff;
			if (sum.coeff != 0)							// ���� �� ����, �� ��������� � �������������� �������
			{
				res.addMonom(sum);
			}
			this->goNext();
			pol.goNext();
		}
	}
	*this = res;
	return *this;
}


Polinom& Polinom::operator-=(Polinom& pol) 
{
	Polinom res;
	this->reset();
	pol.reset();

	while (!this->isEnd() || !pol.isEnd()) 
	{
		if (this->isEnd()) 
		{
			if (!pol.isEnd()) 
			{
				Monom tmp = pol.getCurrent();
				tmp.coeff = -tmp.coeff;				// �������� ���� ������������
				res.addMonom(tmp);
				pol.goNext();
			}
		}
		else if (pol.isEnd())
		{
			res.addMonom(this->getCurrent());
			this->goNext();
		}
		else if (pol.getCurrent() > this->getCurrent()) 
		{
			Monom tmp = pol.getCurrent();
			tmp.coeff = -tmp.coeff;						// �������� ���� ������������
			res.addMonom(tmp);
			pol.goNext();
		}
		else if (this->getCurrent() > pol.getCurrent()) 
		{
			res.addMonom(this->getCurrent());
			this->goNext();
		}
		else 
		{
			Monom sum = this->getCurrent();
			sum.coeff -= pol.getCurrent().coeff;		// �������� ������������
			if (sum.coeff != 0) 
			{
				res.addMonom(sum);
			}
			this->goNext();
			pol.goNext();
		}
	}
	*this = res;
	return *this;
}





















