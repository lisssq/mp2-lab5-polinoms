#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>


template <typename T>
struct Node
{
	T val;			// �������� � ����
	Node* pNext;	// ��������� �� ����.����

	Node() : pNext(nullptr) {} // ����������� �� ��������� (�������������� ������ ���������)

	Node(const T& value, Node* next = nullptr) : val(value), pNext(next) {} // ����������� � ����������
};


template <typename T>
class List			// ����� ������
{
protected:
	Node<T>* pFirst;		// ��������� �� ������ �������
	Node<T>* pLast;			// ��������� �� ��������� �������
	Node<T>* pCurr;
	Node<T>* pPrev;
	int sz;					// ���-�� ��������� � ������

public:

	List();					// ������ ������ 
	~List();

	List(const List& other);

	void insFirst(T elem);	// ���������� �������� � ������ ������
	void delFirst();		// �������� �������� �� ������ ������
	void insLast(T elem);	// ���������� �������� � ����� ������
	void delLast();			// �������� �������� �� ����� ������
	void delCurr();			// ������� ������� ������� ������
	void insCurr(T elem);


	bool isEmpty() const;	// �������� �� �������


	void reset();			// ������������� �������� � ������
	void goNext();			// ������� � ���������� ��������
	bool isEnd();			// �������� ��������� �� ����� ������

	T getCurrent();		// �������� ������� ��������	


	List& operator=(const List& other);



	friend std::ostream& operator<<(std::ostream& out, const List<T>& list)
	{
		Node<T>* tmp = list.pFirst;				// �������� � ������� ��������
		while (tmp != nullptr)
		{
			out << tmp->val;					// ������� �������� ����
			if (tmp->pNext != nullptr)			// ���� ���� ���������, �� 
			{
				out << " + ";					// ��������� �������� �������
			}
			tmp = tmp->pNext;					// ��������� ������
		}
		return out;
	}

};





///////////////////////


template <class T>
List<T>::List() : pFirst(nullptr), pLast(nullptr), sz(0) {}		// �����������

template <class T>
List<T>::List(const List& other) : pFirst(nullptr), pLast(nullptr), sz(0) {
	Node<T>* pCurr = other.pFirst;
	while (pCurr) 
	{
		insLast(pCurr->val);
		pCurr = pCurr->pNext;
	}
}

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
	Node<T>* tmp = new Node<T>;// (elem);	// ����� ���� � �������
	tmp->val = elem;
	tmp->pNext = pFirst;				// ����� ���� ��������� �� ������� ������
	//pFirst = node;						// ������ ������ ���� - �����

	if (pFirst == nullptr)				// ���� ������ ��� ������, �� ��������� ������� ��� �� ��� � ������
	{
		pLast = tmp;
		pFirst = tmp;
	}
	sz++;
}


template <class T>
void List<T>::delFirst()				// ������� �� ������
{
	if (pFirst==nullptr)						// ���� ������ ����, �� ������ �������
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
	Node<T>* tmp = new Node<T>;// (elem);	// ������� ����� ���� 
	tmp->val = elem;
	if (pLast)
	{
		pLast->pNext = tmp;
	}
	else 
	{
		pFirst = tmp;
	}
	pLast = tmp;
	sz++;
}

template <class T>
void List<T>::delLast()
{
	if (pFirst == nullptr)						// ���� ������ ����, �� ������ �������
	{
		return;
	}
	if (pFirst == pLast)				// ���� � ������ ���� ������� 
	{
		delete pFirst;					// ������� ����
		pFirst = nullptr;				// ������������� ��������� � �������
		pLast = nullptr;
		//sz--;
		return;
	}
	else
	{
		Node<T>* tmp = pFirst;				// ��������� ���������
		while (tmp->pNext != pLast)			// ���� �� ������������� �������� 
		{
			tmp = tmp->pNext;				// ��������� � ���������� ��������
		}
		delete pLast;						// ������� ���������
		pLast = tmp;						// ������������� ���������� ���������	
		pLast->pNext = nullptr;				// ��������� ���������� �������� = �������
	
	}
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
	if (pCurr == nullptr)
	{
		return;
	}
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}


template<class T>
bool List<T>::isEnd()
{
	return pCurr == nullptr;
}


template<class T>
void List<T>::delCurr()		// ������� ������� ������� ������
{
	if (isEmpty() || pFirst == nullptr)		// ���� ������ ���� �� ������
	{
		return;
	}
	if (pCurr == pFirst)		// ���� ������� ������� ��� ������ �������
	{
		delFirst();				// ������� ������
		reset();
		return;
	}
	if (pCurr == pLast)			// ���� ������� ������� ��� ��������� �������
	{
		delLast();				// ������� 
		reset();
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

template<class T>
void List<T>::insCurr(T elem)		// 
{
	if (pCurr == pFirst)
	{
		insFirst(elem);
		pPrev = pFirst;
		return;
	}
	if (pPrev == pLast)
	{
		insLast(elem);
		return;
	}
	Node<T>* tmp = new Node<T>(elem);
	tmp->pNext = pCurr; // ������������� ����� � �����

	pPrev->pNext = tmp;
	pPrev = pPrev->pNext;
	sz++;
}

template<class T>
T List<T>::getCurrent() 
{
	if (pCurr != nullptr)
	{
		return pCurr->val;
	}
}


template <typename T>
List<T>& List<T>:: operator=(const List& other) 
{
	if (this == &other) return *this;
	while (pFirst) 
	{
		delFirst();
	}
	Node<T>* pCurr = other.pFirst;
	while (pCurr)
	{
		insLast(pCurr->val);
		pCurr = pCurr->pNext;
	}
	return *this;
}