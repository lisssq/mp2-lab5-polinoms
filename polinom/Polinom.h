#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <string>
#include <sstream> // Добавляем include для std::ostringstream
#include <vector>
#include "Monom.h"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // конструктор по умолчанию
	Polinom(const Polinom& p);						// конструктор копирования
	Polinom(Monom* p, int size);                    // конструктор с массивом мономов
	~Polinom();

	void addMonom(Monom m);							// добавление монома в полином

	Polinom operator+(Polinom& other);				// для сложения полиномов
	Polinom operator-(Polinom& other);				// для вычитания полиномов
	Polinom operator*(double constanta);		    // умножение полинома на константу
	Polinom operator*(Monom& m);					// умножение полинома на моном
	bool operator==(Polinom& other);

	Polinom& operator+=(Polinom& pol);
	Polinom& operator-=(Polinom& pol);


	friend std::ostream& operator<<(std::ostream& out, const Polinom& p)
	{
		if (p.pFirst == nullptr) // Если полином пуст, выводим ноль
		{
			out << "0";
			return out;
		}

		Node<Monom>* tmp = p.pFirst;
		bool isFirst = true;
		bool hasNonZero = false; // Флаг для проверки, есть ли ненулевые мономы

		while (tmp != nullptr)
		{
			double coeff = tmp->val.coeff;

			if (coeff != 0) // Проверяем, что коэффициент не равен нулю
			{
				hasNonZero = true; // Устанавливаем флаг, если нашли ненулевой моном

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

				out << coeff; // Выводим коэффициент

				// Выводим степени x, y, z
				out << "x^" << tmp->val.x;
				out << "y^" << tmp->val.y;
				out << "z^" << tmp->val.z;
			}

			tmp = tmp->pNext;
			isFirst = false;
		}

		if (!hasNonZero) // Если не было ненулевых мономов, выводим "0"
		{
			out << "0";
		}

		return out;
	}
};


std::istream& operator>>(std::istream& in, Polinom& pol)		// ввод мономов в полином
{
	int numMonoms;
	std::cout << "Введите количество мономов в полиноме: ";
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
	oss << p;				// вывод полинома в ostringstream
	return oss.str();
}



Polinom::Polinom() {};

Polinom::Polinom(const Polinom& p) : List<Monom>(p)
{
}


Polinom::Polinom(Monom* p, int size)            // конструктор с массивом мономов
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

void Polinom::addMonom(Monom m)                 // добавление монома в полином
{
	if (pFirst == nullptr)                      // если список пуст, добавляем в конец
	{
		insLast(m);
		return;
	}

	reset();									// возвращаемся в начало списка

	while (!isEnd() && pCurr->val > m)			// пока не конец списка и текущий моном больше добавляемого
	{	
		goNext();								// идем дальше
	}

	if (!isEnd() && pCurr->val == m)			// если текущее и добавляемый моном равны, то 
	{
		pCurr->val.coeff += m.coeff;			// складываем коэффициенты

		if (pCurr->val.coeff == 0)				// если он занулился - удаляем
		{
			delCurr();
		}
	}
	else										// если моном больше текущего, вставляем перед ним
	{
		Node<Monom>* tmp = new Node<Monom>{ m, pCurr }; // создаем новый узел

		if (pPrev == nullptr)					// если моном должен стать первым
		{
			pFirst = tmp;
		}
		else 
		{
			pPrev->pNext = tmp;					// иначе связываем предыдущий элемент с новым
		}

		if (pCurr == nullptr)					// если новый моном должен быть последний
		{
			pLast = tmp;
		}
		sz++;
	}
}


Polinom Polinom::operator+(Polinom& other)
{
	Polinom res(*this);						// копируем текущий полином

	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();		// получаем текущий моном
		res.addMonom(tmp);					// добавляем текущий моном в результат
	}
	return res;
}

Polinom Polinom::operator-(Polinom& other)
{
	Polinom res(*this);
	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		tmp.coeff = -tmp.coeff;				// меняем коэффициент у монома
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
	if (sz != other.sz)							// если размеры полиномов не равны, то сами полиномы очевидно тоже
	{
		return false;
	}
	reset();									// идем в начало обоих полиномов
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
				tmp.coeff = -tmp.coeff;				// изменяем знак коэффициента
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
			tmp.coeff = -tmp.coeff;						// изменяем знак коэффициента
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
			sum.coeff -= pol.getCurrent().coeff;		// вычитаем коэффициенты
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





















