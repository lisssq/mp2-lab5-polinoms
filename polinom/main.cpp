#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"


int main() 
{   
    setlocale(LC_ALL, "Russian");


    Monom m1;               // по умолчанию будет 0
    Monom m2(2.5, 1, 2, 3);
    Monom m3(10.0, 3, 2, 1);
    Monom m4(1.0, 2, 1, 0); 
    Monom m5(2.5, 1, 2, 3);

    // вывод мономов
    std::cout << "m1 = " << m1 << std::endl;
    std::cout << "m2 = " << m2 << std::endl;
    std::cout << "m3 = " << m3 << std::endl;
    std::cout << "m4 = " << m4 << std::endl;
    std::cout << "m5 = " << m5 << std::endl;
    
    // проверка операторов сравнения
    std::cout << "m2 меньше m3?: " << (m2 < m3) << std::endl;
    std::cout << "m2 больше m3?: " << (m2 > m3) << std::endl;
    std::cout << "m2 == m5: " << (m2 == m5) << std::endl;

    // проверка сеттера
    m1.SetCoeff(1.5);
    m1.SetXYZ(3, 0, 2);
    std::cout << "обновленный m1: " << m1 << std::endl;

    std::cout << "---------------------------" << std::endl;


    Polinom poly;           // создание полинома

    // Добавление мономов
    poly.addMonom(m1);
    poly.addMonom(m2);
    poly.addMonom(m3);
    poly.addMonom(m4);
    poly.addMonom(m5);

    // Вывод полинома
    std::cout << "полином: " << poly << std::endl;


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