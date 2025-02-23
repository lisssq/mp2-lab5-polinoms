#pragma once
#include "Monom.h"
#include "Monom.cpp"


class Polynom :public List<Monom>
{
public:

	Polynom() : List<Monom>() {}  // Конструктор по умолчанию (создаёт пустой полином)

	friend std::ostream& operator<<(std::ostream& out, const Polynom& p)
	{
		if (p.pFirst == nullptr) {
			out << "0";
			return out;
		}

		Node<Monom>* temp = p.pFirst;
		bool first = true; // Чтобы не ставить лишний плюс в начале

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

	Polynom(Monom* p, int size)
	{
		for (int i = 0; i < size; i++)
		{
			insLast(p[i]);
		}
	}



	void addMonom(Monom m)
	{
		if (pFirst == nullptr)		// если список пуст, то просто добавляем моном
		{
			insLast(m);
			return;
		}
		if (m > pFirst->val)		// если моном больше первого, то вставляем его в начало списка
		{
			insFirst(m);
			return;
		}
		if (m < pLast->val)			// если моном меньше последнего, вставляем в конец списка
		{
			insLast(m);
			return;
		}

		for (reset(); !isEnd(); goNext())
		{
			if (m == pCurr->val) // Если нашли моном с такой же степенью, складываем коэффициенты
			{
				pCurr->val.coeff += m.coeff;
				if (pCurr->val.coeff == 0) // Если коэффициент стал 0, удаляем моном
				{
					delCurr();
				}
				return;
			}
			else if (m > pCurr->val) // Если моном больше текущего, вставляем перед ним
			{
				Node<Monom>* tmp = new Node<Monom>;
				tmp->val = m;
				tmp->pNext = pCurr;
				pPrev->pNext = tmp;
				return;
			}
		}
	}


};