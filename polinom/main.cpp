#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <locale.h>
#include "Monom.h"
//using namespace std;

int main() 
{   
    setlocale(LC_ALL, "Russian");


    // �������� ������� � ������� �������������� � ���������
    Monom m1; // ������ ���� 0 (�� ���������)
    Monom m2(3.5, 2, 1, 0);
    Monom m3(5.0, 1, 2, 3);
    Monom m4(2.0, 2, 1, 0); // ����������� m2 �� ��������, �� � ������ �������������

    // ����� �������
    std::cout << "m1 = " << m1 << std::endl;
    std::cout << "m2 = " << m2 << std::endl;
    std::cout << "m3 = " << m3 << std::endl;
    std::cout << "m4 = " << m4 << std::endl;
    
    // �������� ���������� ���������
    std::cout << "m2 < m3: " << (m2 < m3) << std::endl;
    std::cout << "m3 > m2: " << (m3 > m2) << std::endl;
    std::cout << "m2 == m4: " << (m2 == m4) << std::endl;

    // �������� ��������
    m1.SetCoeff(1.5);
    m1.SetXYZ(3, 0, 2);
    std::cout << "����������� m1: " << m1 << std::endl;

    return 0;
}








//using namespace std;
//int main()
//{
//    vector<int> v = { 1,2,3,4,5 };
//    vector <int>::iterator i;
//    for (i = v.begin(); i != v.end(); i++)
//    {
//        cout << *i;
//    }
//}