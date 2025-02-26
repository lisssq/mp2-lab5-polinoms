#pragma once
#include <iostream>


template <typename T>
struct Node
{
	T val;			// �������� � ����
	Node* pNext;	// ��������� �� ����.����

	Node() : pNext(nullptr) {} // ����������� �� ��������� (�������������� ������ ���������)

	Node(const T& value) : val(value), pNext(nullptr) {} // ����������� � ����������
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


	bool isEmpty() const;	// �������� �� �������


	void reset();			// ������������� �������� � ������
	//void reset() const;
	void goNext();			// ������� � ���������� ��������
	//void goNext() const;
	bool isEnd();			// �������� ��������� �� ����� ������
	//bool isEnd() const;

	T getCurrent();		// �������� ������� ��������	


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

	Node<T>* tmp = pFirst;				// ��������� ���������
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

//template <class T>
//void List<T>::reset() const
//{
//	pCurr = pFirst;
//	pPrev = nullptr;
//}

template<class T>
void List<T>::goNext()
{
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}

//template<class T>
//void List<T>::goNext() const
//{
//	pPrev = pCurr;
//	pCurr = pCurr->pNext;
//}

template<class T>
bool List<T>::isEnd()
{
	/*if (pCurr->pNext == nullptr)
	{
		return true;
	}*/
	return pCurr == nullptr;
}

//template<class T>
//bool List<T>::isEnd() const
//{
//	return pCurr == nullptr;
//}


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

template<class T>
T List<T>::getCurrent() 
{
	if (pCurr != nullptr)
	{
		return pCurr->val;
	}
		
}
