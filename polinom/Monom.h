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

	Monom();
	Monom(double _coeff, int x, int y, int z);

	void SetCoeff(double _coeff);
	void SetXYZ(int _x, int _y, int _z);

	bool operator<(const Monom& m) const;
	/*
	{
		bool res = false;
		if (x < m.x)
		{
			if (y < m.y)
			{
				if (z < m.z)
				{
					res = true;
				}
			}
		}
		return res;
	}*/

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
	T val;
	Node* pNext;
};


template <typename T>
class List
{
protected:
	Node<T> *pFirst, *pLast;
	int sz;
	
public:

	List();
	~List();

	void insFirst(T elem);
	void delFirst();
	void insLast(T elem);

	bool isEmpty() const;

};

