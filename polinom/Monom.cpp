#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include "Monom.h"


 
Monom::Monom() : coeff(0), x(0), y(0), z(0) {}			// ����������� �� ���������


Monom::Monom(double _coeff, int _x, int _y, int _z)		// ����������� � �����������
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


bool Monom::operator<(const Monom& m) const				// ��������� ��������� (������������������ �������)
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


template <class T>
List<T>::List() : pFirst(nullptr), pLast(nullptr), sz(0) {}		// �����������


template <class T>
List<T>::~List()			// ����������
{
	while (!isEmpty())
	{
		delFirst();
	}
}


template <class T>
bool List<T>::isEmpty() const			// �������� �� �������
{
	return pFirst == nullptr;
}


template <class T>
void List<T>::insFirst(T elem)			// ������� � ������
{
	Node<T>* node = new Node<T>(elem);	// ����� ���� � �������
	node->pNext = pFirst;				// ����� ���� ��������� �� ������� ������
	pFirst = node;						// ������ ������ ���� - �����

	if (pLast == nullptr)				// ���� ������ ��� ������, �� ��������� ������� ��� �� ��� � ������
	{  
		pLast = node;
	}
	sz++;
}


template <class T>
void List<T>::delFirst()				// ������� �� ������
{
	if (isEmpty())						// ���� ������ ����, �� ������ �������
	{
		return;
	}
	Node<T>* tmp = pFirst;				// ��������� ��������� �� ������ ����
	pFirst = pFirst->pNext;				// ��������� �� ��������� ����
	delete tmp;							// ������� ����� ������ ����
	if (pFirst == nullptr)				// ���� ������ ���� ������ �� ��������� ������� ������� = nullptr
	{
		pLast = nullptr;
	}
	sz--;
}

template <class T>
void List<T>::insLast(T elem)			// ������� � �����
{
	Node<T>* tmp = new Node<T>(elem);	// ������� ����� ���� 
	if (pFirst == nullptr)				// ���� ������ ���� �� ������ � ��������� ���� = ������ ���� tmp
	{
		pFirst = pLast = tmp;
	}	
	else								// ����� ��������� � �����
	{
		pLast->pNext = tmp;				// ��������� � ���������� �� ��������� �� ���
		pLast = tmp;					// � ������ ��������� = tmp
	}
	sz++;
}

template <class T>
void List<T>::delLast()
{
	if (isEmpty())						// ���� ������ ����, �� ������ �������
	{
		return;
	}
	if (pFirst == pLast)				// ���� � ������ ���� ������� 
	{
		delete pFirst;					// ������� ����
		pFirst = nullptr;				// ������������� ��������� � �������
		pLast = nullptr;
		sz--;
		return;
	}

	Node<T> *tmp = pFirst;				// ��������� ���������
	while (tmp->pNext != pLast)			// ���� �� ������������� �������� 
	{
		tmp = tmp->pNext;				// ��������� � ���������� ��������
	}
	delete pLast;						// ������� ���������
	pLast = tmp;						// ������������� ���������� ���������	
	pLast->pNext = nullptr;				// ��������� ���������� �������� = �������
	sz--;
}

template <class T>
void List<T>::reset()
{
	pCurr = pFirst;
	pPrev = nullptr;
}

template<class T>
void List<T>::goNext()
{
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}

template<class T>
bool List<T>::isEnd()
{
	/*if (pCurr->pNext == nullptr)
	{
		return true;
	}*/
	return pCurr == nullptr;
}


template<class T>
void List<T>::delCurr()		// ������� ������� ������� ������
{
	if (pFirst == nullptr)		// ���� ������ ���� �� ������
	{
		return;
	}
	if (pCurr == pFirst)		// ���� ������� ������� ��� ������ �������
	{
		delFirst();				// ������� ������
		pCurr = nullptr;		// �������� ������� ��������� ����� ��������
		return;
	}
	if (pCurr == pLast)			// ���� ������� ������� ��� ��������� �������
	{
		delLast();				// ������� 
		pCurr = nullptr;		// �������� ������� ��������� ����� ��������
		return;
	}

	pPrev->pNext = pCurr->pNext;	// ������������ �������� �� ���������� � ����������� �� ��������
	delete pCurr;					// ������� �������
	pCurr = pPrev->pNext;			// ���������� ������� �� ���������

	if (pCurr == nullptr)			// ���� ������� ��������� �������
	{
		pLast = pPrev;				// �� pPrev ������ ���������
	}

	sz--;				// ��������� ������ ������

}