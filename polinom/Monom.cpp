#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include "Monom.h"




// ����������� �� ���������
Monom::Monom() : coeff(0), x(0), y(0), z(0) {}

// ����������� � �����������
Monom::Monom(double _coeff, int _x, int _y, int _z)
	: coeff(_coeff), x(_x), y(_y), z(_z) {}

// �������
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


// ��������� ��������� (������������������ �������)
bool Monom::operator<(const Monom& m) const
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




//----------------------------------------------------


// �����������
template <class T>
List<T>::List() : pFirst(nullptr), pLast(nullptr), sz(0) {}

// ����������
template <class T>
List<T>::~List()
{
	while (!isEmpty())
	{
		delFirst();
	}
}

// �������� �� �������
template <class T>
bool List<T>::isEmpty() const
{
	return pFirst == nullptr;
}


template <class T>
void List<T>::insFirst(T elem)
{
	Node<T>* node = new Node<T>(elem);
	node->pNext = pFirst;
	pFirst = node;

	if (pLast == nullptr)
	{  // ���� ��� ������ �������, pLast ���� ��������� �� ����
		pLast = node;
	}
	sz++;
}


template <class T>
void List<T>::delFirst()
{
	if (isEmpty())
	{
		return;
	}
	Node<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
	if (pFirst == nullptr)	 // ���� ������ ���� ������, pLast ���� ������ ����������
	{
		pLast = nullptr;
	}
	sz--;
}

template <class T>
void List<T>::insLast(T elem)
{
	Node<T>* tmp = new Node<T>(elem);
	if (pFirst == nullptr)		// ���� ������ ����
	{
		pFirst = pLast = tmp;
	}
	else
	{
		pLast->pNext = tmp;
		pLast = tmp;
	}
	sz++;
}