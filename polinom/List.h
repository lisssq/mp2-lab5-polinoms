#pragma once
#include <iostream>


template <typename T>
struct Node
{
	T val;			// значение в узле
	Node* pNext;	// указатель на след.узел

	Node() : pNext(nullptr) {} // Конструктор по умолчанию (инициализирует только указатель)

	Node(const T& value) : val(value), pNext(nullptr) {} // Конструктор с параметром
};


template <typename T>
class List			// класс списка
{
protected:
	Node<T>* pFirst;		// указатель на первый элемент
	Node<T>* pLast;			// указатель на последний элемент
	Node<T>* pCurr;
	Node<T>* pPrev;
	int sz;					// кол-во элементов в списке

public:

	List();					// пустой список 
	~List();

	List(const List& other);

	void insFirst(T elem);	// добавление элемента в начало списка
	void delFirst();		// удаление элемента из начала списка
	void insLast(T elem);	// добавление элемента в конец списка
	void delLast();			// удаление элемента из конца списка
	void delCurr();			// удалить текущий элемент списка


	bool isEmpty() const;	// проверка на пустоту


	void reset();			// устанавливает итератор в начало
	//void reset() const;
	void goNext();			// переход к следующему элементу
	//void goNext() const;
	bool isEnd();			// проверка достигнут ли конец списка
	//bool isEnd() const;

	T getCurrent();		// получить текущее значение	


	friend std::ostream& operator<<(std::ostream& out, const List<T>& list)
	{
		Node<T>* tmp = list.pFirst;				// начинаем с первого элемента
		while (tmp != nullptr)
		{
			out << tmp->val;					// выводим значение узла
			if (tmp->pNext != nullptr)			// если есть следующий, то 
			{
				out << " + ";					// разделяем элементы плюсами
			}
			tmp = tmp->pNext;					// переходим дальше
		}
		return out;
	}

};





///////////////////////


template <class T>
List<T>::List() : pFirst(nullptr), pLast(nullptr), sz(0) {}		// конструктор

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

	Node<T>* tmp = pFirst;				// временный указатель
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

template<class T>
T List<T>::getCurrent() 
{
	if (pCurr != nullptr)
	{
		return pCurr->val;
	}
		
}
