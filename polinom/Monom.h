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

	Monom();		// ����� � �������� �����������	

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
	T val;			// �������� � ����
	Node* pNext;	// ��������� �� ����.����

	Node() : pNext(nullptr) {} // ����������� �� ��������� (�������������� ������ ���������)

	Node(const T& value) : val(value), pNext(nullptr) {} // ����������� � ����������
};


template <typename T>
class List			// ����� ������
{
protected:
	Node<T>* pFirst;		// ��������� �� ������ �������
	Node<T>* pLast;			// ��������� �� ��������� �������
	Node<T>* pCurr;
	Node<T>* pPrev;
	int sz;					// ���-�� ��������� � ������
	
public:

	List();					// ������ ������ 
	~List();

	void insFirst(T elem);	// ���������� �������� � ������ ������
	void delFirst();		// �������� �������� �� ������ ������
	void insLast(T elem);	// ���������� �������� � ����� ������
	void delLast();			// �������� �������� �� ����� ������
	void delCurr();			// ������� ������� ������� ������


	bool isEmpty() const;	// �������� �� �������


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
				out << " + "; // ��������� �������� �������
			}
			temp = temp->pNext;
		}
		return out;
	}

};

