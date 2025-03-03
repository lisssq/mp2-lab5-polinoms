#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Polinom.h"
#include "Monom.h"
#include "List.h"


std::ostream& operator<<(std::ostream& out, const Polinom& p) 
{
    if (p.pFirst == nullptr)                    // если полином пуст, то сразу выыводим "0"
    {
        out << "0";
        return out;
    }

    Node<Monom>* tmp = p.pFirst;                // начинаем с первого элемента
    bool isFirst = true;                          // чтобы не ставить лишний плюс в начале

    while (tmp != nullptr)
    {
        if (!isFirst && tmp->val.coeff > 0)       // если это не первый и не нулевой моном, то добавляем знак "+"
            out << " + ";

        out << tmp->val;                        // выводим значения монома
        tmp = tmp->pNext;                       // переходим на следующий узел
        isFirst = false;                        // ставим флаг что это не первый моном (чтоб дальше ставился знак "+")
    }

    return out;
}



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

    for (reset(); !isEnd(); goNext())           // начинаем с reset() - ставит pCurr на 1-й элемент списка, идем до тех пор пока не дойдем до конца, двигаемся к след.элементу
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
            Node<Monom>* tmp = new Node<Monom>(m);; // создаем новый узел
            tmp->val = m;                       // записываем наш моном в новый узел
            tmp->pNext = pCurr;                 // связываем новый узел с текузим
            pPrev->pNext = tmp;                 // связываем предыдущий узел с новым
            return;
        }
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