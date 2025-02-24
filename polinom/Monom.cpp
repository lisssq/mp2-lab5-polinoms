#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include "Monom.h"


 
Monom::Monom() : coeff(0), x(0), y(0), z(0) {}			// конструктор по умолчанию


Monom::Monom(double _coeff, int _x, int _y, int _z)		// конструктор с параметрами
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


bool Monom::operator<(const Monom& m) const				// операторы сравнения (лексикографический порядок)
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
List<T>::List() : pFirst(nullptr), pLast(nullptr), sz(0) {}		// конструктор


template <class T>
List<T>::~List()			// деструктор
{
	while (!isEmpty())
	{
		delFirst();
	}
}


template <class T>
bool List<T>::isEmpty() const			// проверка на пустоту
{
	return pFirst == nullptr;
}


template <class T>
void List<T>::insFirst(T elem)			// вставка в начало
{
	Node<T>* node = new Node<T>(elem);	// новый узел с данными
	node->pNext = pFirst;				// новый узел указывает на текущий первый
	pFirst = node;						// теперь первый узел - новый

	if (pLast == nullptr)				// если список был пустым, то последний элемент тот же что и первый
	{  
		pLast = node;
	}
	sz++;
}


template <class T>
void List<T>::delFirst()				// удаляем из начала
{
	if (isEmpty())						// если список пуст, то просто выходим
	{
		return;
	}
	Node<T>* tmp = pFirst;				// сохраняем указатель на первый узел
	pFirst = pFirst->pNext;				// переходим на следующий узел
	delete tmp;							// удаляем самый первый узел
	if (pFirst == nullptr)				// если список стал пустым то последний элемент логично = nullptr
	{
		pLast = nullptr;
	}
	sz--;
}

template <class T>
void List<T>::insLast(T elem)			// вставка в конец
{
	Node<T>* tmp = new Node<T>(elem);	// создаем новый узел 
	if (pFirst == nullptr)				// если список пуст то первый и последний узел = новому узлу tmp
	{
		pFirst = pLast = tmp;
	}	
	else								// иначе добавляем в конец
	{
		pLast->pNext = tmp;				// переходим с последнего на следующий за ним
		pLast = tmp;					// и делаем последний = tmp
	}
	sz++;
}

template <class T>
void List<T>::delLast()
{
	if (isEmpty())						// если список пуст, то просто выходим
	{
		return;
	}
	if (pFirst == pLast)				// если в списке один элемент 
	{
		delete pFirst;					// удаляем узел
		pFirst = nullptr;				// устанавливаем указатели в нуллптр
		pLast = nullptr;
		sz--;
		return;
	}

	Node<T> *tmp = pFirst;				// временный указатель
	while (tmp->pNext != pLast)			// идем до предполеднего элемента 
	{
		tmp = tmp->pNext;				// переходим к следующему элементу
	}
	delete pLast;						// удаляем последний
	pLast = tmp;						// предпоследний становится последним	
	pLast->pNext = nullptr;				// указатель последнего элемента = нуллптр
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
void List<T>::delCurr()		// удаляем текущий элемент списка
{
	if (pFirst == nullptr)		// если список пуст то ничего
	{
		return;
	}
	if (pCurr == pFirst)		// если текущий элемент это первый элемент
	{
		delFirst();				// удаляем первый
		pCurr = nullptr;		// обнуляем текущий указатель после удаления
		return;
	}
	if (pCurr == pLast)			// если текущий элемент это последний элемент
	{
		delLast();				// удаляем 
		pCurr = nullptr;		// обнуляем текущий указатель после удаления
		return;
	}

	pPrev->pNext = pCurr->pNext;	// переписываем указатль на предыдущий в зависимости от текущего
	delete pCurr;					// удаляем текущий
	pCurr = pPrev->pNext;			// перемещаем текущий на следубщий

	if (pCurr == nullptr)			// если удалили последний элемент
	{
		pLast = pPrev;				// то pPrev теперь последний
	}

	sz--;				// уменьшаем размер списка

}