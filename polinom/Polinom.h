#pragma once
#include "Monom.h"
#include "Monom.cpp"


class Polynom :public List<Monom>
{
public:
	Polynom(Monom* p, int size)
	{
		for (int i = 0; i < size; i++)
		{
			insLast(p[i]);
		}
	}

	void addMonom(Monom m)
	{
		if (pFirst == nullptr)
		{
			insLast(m);
		}
		else
		{
			if (m > pFirst->val)
			{
				insFirst(m);
			}
		}
		if (m < pLast->val)
		{
			insLast(m);
		}

		for (reset(); !isEnd(); goNext())
		{
			if (m >= pCurr->val)
			{
				if (m > pCurr->val)
				{
					Node<Monom>* tmp = new Node<Monom>;
					tmp->val = m;
					tmp->pNext = pCurr;
					pPrev->pNext = tmp;
				}
				else
				{
					double c;
					c = pCurr->val.coeff + m.coeff;
					if (c != 0)
					{
						pCurr->val.coeff = c;
					}
					else
					{
						Node<Monom>* tmp = pCurr;
						pCurr = pCurr->pNext;
						pPrev->pNext = pCurr;
						delete tmp;
					}
				}
			}
		}
	}

	void delCurr();
};