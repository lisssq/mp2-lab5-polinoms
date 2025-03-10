#include <iostream>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"

int main() 
{
    setlocale(LC_ALL, "Russian");

    std::vector<Polinom> polinoms;              // вектор полином который будет хранить полиномчики (объекты типа "полином")

    while (true)
    {
        std::cout << "Выбери действие:" << std::endl;
        std::cout << "1. Ввести полином" << std::endl;
        std::cout << "2. Выполнить операцию над полиномами" << std::endl;
        std::cout << "3. Вывести все полиномы" << std::endl;
        std::cout << "0. Выйти" << std::endl;

        int num;        // номер действия
        std::cin >> num;

        if (num == 0)
        {
            break;
        }

        switch (num)
        {
        case 1:                                             // если "ввести полином"
        {
            Polinom p;
            std::cout << "Введите полином:" << std::endl;
            std::cin >> p;                                  // вводим полином
            polinoms.push_back(p);
            std::cout << "Полином добавлен." << std::endl;
            break;
        }
        case 2:                                             // если "выполнить операцию над полиномами"
        {
            if (polinoms.empty())                           // если вектор полиномов пуст
            {
                std::cout << "Необходимо ввести хотя бы один полином." << std::endl;
                break;
            }

            std::cout << "Выберите операцию:" << std::endl;
            std::cout << "1. Сложение полиномов" << std::endl;
            std::cout << "2. Вычитание полиномов" << std::endl;
            std::cout << "3. Умножение полинома на константу" << std::endl;
            std::cout << "4. Умножение полинома на моном" << std::endl;
            //std::cout << "5. Умножение полиномов" << std::endl;

            int operation;
            std::cin >> operation;                          // вводим номер операции

            if (operation == 1 || operation == 2 || operation == 5)
            {
                if (polinoms.size() < 2)                    // если полиномов для операции не достаточно
                {
                    std::cout << "Для этой операции необходимо минимум два полинома." << std::endl;
                    break;
                }
            }


            std::cout << "Введите номер первого полинома (начиная с 0): ";
            int index1, index2 = 0;                         // индексы полиномов в векторе хранения
            std::cin >> index1;                             // вводим номер первого полинома и проверяем корректность

            if (index1 < 0 || index1 >= polinoms.size())
            {
                std::cout << "Некорректный индекс полинома." << std::endl;
                break;
            }


            if (operation == 1 || operation == 2 || operation == 5)     // если полинома надо два, то вводим второй номер полинома
            {
                std::cin >> index2;
                if (index2 < 0 || index2 >= polinoms.size())
                {
                    std::cout << "Некорректный индекс полинома." << std::endl;
                    break;
                }
            }

            switch (operation)
            {
            case 1:
            {
                Polinom sum = polinoms[index1] + polinoms[index2];
                std::cout << "Сумма полиномов: " << sum << std::endl;

                polinoms.push_back(sum);        // добавляем результат в вектор
                std::cout << "Результат добавлен в вектор полиномов." << std::endl;
                break;
            }
            case 2:
            {
                Polinom sub = polinoms[index1] - polinoms[index2];
                std::cout << "Разность полиномов: " << sub << std::endl;

                polinoms.push_back(sub);       // добавляем результат в вектор
                std::cout << "Результат добавлен в вектор полиномов." << std::endl;
                break;
            }
            case 3:
            {
                double constant;
                std::cout << "Введите константу: ";
                std::cin >> constant;
                Polinom mulByConst = polinoms[index1] * constant;
                std::cout << "Результат умножения на константу: " << mulByConst << std::endl;

                polinoms.push_back(mulByConst);     // добавляем результат в вектор    
                std::cout << "Результат добавлен в вектор полиномов." << std::endl;
                break;
            }
            case 4:
            {
                Monom mon;
                std::cout << "Введите моном для умножения: " << std::endl;
                std::cin >> mon;
                Polinom mulByMonom = polinoms[index1] * mon;
                std::cout << "Результат умножения на моном: " << mulByMonom << std::endl;

                polinoms.push_back(mulByMonom); // Добавляем результат в вектор
                std::cout << "Результат добавлен в вектор полиномов." << std::endl;
                break;
            }
            // case 5:
            //{
            //     Polinom mulByPolinom = polinoms[index1] * polinoms[index2];
            //     std::cout << "Результат умножения полиномов: " << mulByPolinom << std::endl;

            //     polinoms.push_back(mulByPolinom); // Добавляем результат в вектор
            //     std::cout << "Результат добавлен в вектор полиномов." << std::endl;
            //     break;
            // }
            }
            break;
        }
        case 3:
        {
            if (polinoms.empty())
            {
                std::cout << "Полиномы не введены." << std::endl;
            }
            else
            {
                for (int i = 0; i < polinoms.size(); i++)
                {
                    std::cout << "Полином " << i << ": " << polinoms[i] << std::endl;
                }
            }
            break;
        }

        }
    }

    return 0;
}


// сделать оператор -=