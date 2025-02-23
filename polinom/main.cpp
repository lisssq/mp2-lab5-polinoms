#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"
/*#include "Polinom.cpp"
#include "Monom.cpp"*/
//using namespace std;

int main() 
{   
    setlocale(LC_ALL, "Russian");


    // Создание мономов с разными коэффициентами и степенями
    Monom m1; // Должен быть 0 (по умолчанию)
    Monom m2(3.5, 2, 1, 0);
    Monom m3(5.0, 1, 2, 3);
    Monom m4(2.0, 2, 1, 0); // Аналогичный m2 по степеням, но с другим коэффициентом

    // Вывод мономов
    std::cout << "m1 = " << m1 << std::endl;
    std::cout << "m2 = " << m2 << std::endl;
    std::cout << "m3 = " << m3 << std::endl;
    std::cout << "m4 = " << m4 << std::endl;
    
    // Проверка операторов сравнения
    std::cout << "m2 < m3: " << (m2 < m3) << std::endl;
    std::cout << "m3 > m2: " << (m3 > m2) << std::endl;
    std::cout << "m2 == m4: " << (m2 == m4) << std::endl;

    // Проверка сеттеров
    m1.SetCoeff(1.5);
    m1.SetXYZ(3, 0, 2);
    std::cout << "Обновленный m1: " << m1 << std::endl;



    //// Создание списка
    //List<Monom> list;

    //// Добавление элементов
    //list.insFirst(m2);
    //list.insLast(m3);
    //list.insFirst(m1);
    //list.insLast(m4);

    //// Вывод списка
    //Node<Monom>* temp = list.pFirst;
    //std::cout << "Список мономов: ";
    //while (temp != nullptr) {
    //    std::cout << temp->val << " -> ";
    //    temp = temp->pNext;
    //}
    //std::cout << "NULL\n";


    //// Удаление элементов
    //list.delFirst();
    //list.delLast();

    //// Вывод списка после удаления
    //temp = list.pFirst;
    //std::cout << "После удаления первого и последнего: ";
    //while (temp != nullptr) {
    //    std::cout << temp->val << " -> ";
    //    temp = temp->pNext;
    //}
    //std::cout << "NULL\n";

    //std::cout << "\n=== Тестирование класса Polynom ===\n";



    // Создание полинома
    Polynom poly;

    // Добавление мономов
    poly.addMonom(m1);
    poly.addMonom(m2);
    poly.addMonom(m3);
    poly.addMonom(m4);

    // Вывод полинома
    std::cout << "Полином: " << poly << std::endl;


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