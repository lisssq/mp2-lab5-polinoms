#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
//using namespace std;
//const int MAX_SZ = 10000;
  

struct Monom
{
	double coeff;
	int x, y, z; 

public:

	Monom();		// моном с нулевыми параметрами	

	Monom(double _coeff, int x, int y, int z);

	void SetCoeff(double _coeff);
	void SetXYZ(int _x, int _y, int _z);

	bool operator<(const Monom& m) const;
	bool operator>(const Monom& m) const;
	bool operator==(const Monom& m) const;

	friend std::ostream& operator<<(std::ostream& out, const Monom& mon)
	{
		out << mon.coeff << "x^" << mon.x << "y^" << mon.y << "z^" << mon.z;
		return out;

	}


};	













template <typename T>
struct Node
{
	T val;			// значение в узле
	Node* pNext;	// указатель на след.узел

	Node() : pNext(nullptr) {} //  онструктор по умолчанию (инициализирует только указатель)

	Node(const T& value) : val(value), pNext(nullptr) {} //  онструктор с параметром
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

	void insFirst(T elem);	// добавление элемента в начало списка
	void delFirst();		// удаление элемента из начала списка
	void insLast(T elem);	// добавление элемента в конец списка
	void delLast();			// удаление элемента из конца списка
	void delCurr();			// удалить текущий элемент списка


	bool isEmpty() const;	// проверка на пустоту


	void reset();
	void goNext();
	bool isEnd();

	void getCurrent();


	friend std::ostream& operator<<(std::ostream& out, const List<T>& list)
	{
		Node<T>* temp = list.pFirst;
		while (temp != nullptr)
		{
			out << temp->val;
			if (temp->pNext != nullptr)
			{
				out << " + "; // раздел€ем элементы плюсами
			}
			temp = temp->pNext;
		}
		return out;
	}

};

