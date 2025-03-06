#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Monom.h"
#include "List.h"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // конструктор по умолчанию
	Polinom(Monom* p, int size);                    // конструктор с массивом мономов
	void addMonom(Monom m);                        // добавление монома в полином

	Polinom operator+(Polinom& other);          // для сложения полиномов
	Polinom operator-(Polinom& other);          // для вычитания полиномов
	Polinom operator*(double constanta);       // умножение полинома на константу
	Polinom operator*(Monom& m);              // умножение полинома на моном
	bool operator==(Polinom& other);

	Polinom& operator+=(Polinom& pol);


	friend std::ostream& operator<<(std::ostream& out, const Polinom& p) 
	{
		if (p.pFirst == nullptr) 
		{
			out << "0";
			return out;
		}

		Node<Monom>* tmp = p.pFirst;
		bool isFirst = true;

		while (tmp != nullptr)
		{
			if (!isFirst && tmp->val.coeff > 0)
				out << " + ";

			out << tmp->val;

			tmp = tmp->pNext;
			isFirst = false;
		}

		return out;
	}

};



std::istream& operator>>(std::istream& in, Polinom& pol) {
	int numMonoms;
	std::cout << "Введите количество мономов в полиноме: ";
	in >> numMonoms;

	for (int i = 0; i < numMonoms; ++i) {
		Monom mon;
		in >> mon;
		pol.addMonom(mon);
	}
	return in;
}









//Polinom::Polinom() : List<Monom>() {}           // конструктор по умолчанию (создаёт пустой полином)

Polinom::Polinom() {};

//Polinom::Polinom(const Polinom& other) : List<Monom>(other) {
//    std::cout << "Конструктор копирования Polinom: " << *this << std::endl;
//}

Polinom::Polinom(Monom* p, int size)            // конструктор с массивом мономов
{
	pFirst = pLast = nullptr;
	sz = 0;
	for (int i = 0; i < size; i++)
	{
		addMonom(p[i]);
	}
}

void Polinom::addMonom(Monom m)                 // добавление монома в полином
{
	if (pFirst == nullptr)                      // если список пуст, добавляем в конец
	{
		insLast(m);
		return;
	}

	reset();

	while (!isEnd() && pCurr->val > m)
	{
		goNext();
	}

	if (!isEnd() && pCurr->val == m)
	{
		pCurr->val.coeff += m.coeff;

		if (pCurr->val.coeff == 0) 
		{
			delCurr();
		}
	}
	else                 // если моном больше текущего, вставляем перед ним
	{
		Node<Monom>* tmp = new Node<Monom>{ m, pCurr }; // создаем новый узел

		if (pPrev == nullptr)
		{
			pFirst = tmp;
		}
		else {
			pPrev->pNext = tmp;
		}

		if (pCurr == nullptr)
		{
			pLast = tmp;
		}

		sz++;
	}

	
}



Polinom Polinom::operator+(Polinom& other)
{
	Polinom res(*this);  // Копируем текущий полином

	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		res.addMonom(tmp);  // Добавляем текущий моном
	}

	return res;
}

Polinom Polinom::operator-(Polinom& other)
{
	Polinom res(*this);
	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		tmp.coeff = -tmp.coeff;     //меняем коэффициент у монома
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


Polinom Polinom:: operator*( Monom& m)
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
	if (sz != other.sz)
	{
		return false;
	}
	reset();
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
	this->reset();								// сбрасываем указатели обоих полиномов в начало
	pol.reset();

	while (!this->isEnd() || !pol.isEnd())		// пока какой-то полином не кончится
	{
		if (this->isEnd())						// если исходный полином кончился
		{
			if (!pol.isEnd())					// но второй еще имеет мономы
			{
				res.addMonom(pol.getCurrent());	// то просто добавляем их в результирующий полином
				pol.goNext();
			}
		}
		else if (pol.isEnd())					// если же второй полином кончился, то делаем то же самое, только с перым
		{
			res.addMonom(this->getCurrent());
			this->goNext();
		}
		else if (pol.getCurrent() > this->getCurrent())	// если степень монома из 2 полинома больше, то добавляем его в результат
		{
			res.addMonom(pol.getCurrent());
			pol.goNext();								// идем к след.моному 2 полинома, указатель у текущего - прежний
		}
		else if (this->getCurrent() > pol.getCurrent()) // если меньше - добавляем из 1
		{
			res.addMonom(this->getCurrent());
			this->goNext();								// и идем к след. в текущем полиноме, указатель во 2 не меняется
		}
		else											// если степени одинаковые
		{
			Monom sum = this->getCurrent();				// то складываем коэфф.при мономах
			sum.coeff += pol.getCurrent().coeff;
			if (sum.coeff != 0)							// если не ноль, то добавляем в результирующий полином
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