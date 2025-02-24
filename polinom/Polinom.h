#pragma once
#include "Monom.h"
#include "Monom.cpp"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // конструктор по умолчанию
	Polinom(Monom* p, int size);                    // конструктор с массивом мономов

	void addMonom(Monom m);                         // добавление монома в полином

	friend std::ostream& operator<<(std::ostream& out, const Polinom& p)
	{
        if (p.pFirst == nullptr) {
            out << "0";
            return out;
        }

        Node<Monom>* temp = p.pFirst;
        bool first = true;                          // чтобы не ставить лишний плюс в начале

        while (temp != nullptr)
        {
            if (!first && temp->val.coeff > 0)
                out << " + ";

            out << temp->val;
            temp = temp->pNext;
            first = false;
        }

        return out;
	}
};





Polinom::Polinom() : List<Monom>() {}           // конструктор по умолчанию (создаёт пустой полином)

Polinom::Polinom(Monom* p, int size)            // конструктор с массивом мономов
{
    for (int i = 0; i < size; i++)
    {
        insLast(p[i]);
    }
}

void Polinom::addMonom(Monom m)                 // добавление монома в полином
{
    if (pFirst == nullptr)                      // если список пуст, добавляем в конец
    {
        insLast(m);
        return;
    }
    if (m > pFirst->val)                        // вставляем в начало, если он больше первого
    {
        insFirst(m);
        return;
    }
    if (m < pLast->val)                         // вставляем в конец, если он меньше последнего
    {
        insLast(m);
        return;
    }

    for (reset(); !isEnd(); goNext())
    {
        if (m == pCurr->val)                    // если нашли моном с такой же степенью, складываем коэффициенты
        {
            pCurr->val.coeff += m.coeff;
            if (pCurr->val.coeff == 0)          // если коэффициент стал 0, удаляем моном
            {
                delCurr();
            }
            return;
        }
        else if (m > pCurr->val)                // если моном больше текущего, вставляем перед ним
        {
            Node<Monom>* tmp = new Node<Monom>;
            tmp->val = m;
            tmp->pNext = pCurr;
            pPrev->pNext = tmp;
            return;
        }
    }
}

