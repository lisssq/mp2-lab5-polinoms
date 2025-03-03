#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "List.h"
//#include "Polinom.h"
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

	friend std::ostream& operator<<(std::ostream& out, const Monom& mon);
	/*{
		out << mon.coeff << "x^" << mon.x << "y^" << mon.y << "z^" << mon.z;
		return out;

	}*/

};	




