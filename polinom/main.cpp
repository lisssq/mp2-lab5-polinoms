
#include <iostream>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Polinom> polinoms;

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Ввести полином" << std::endl;
        std::cout << "2. Выполнить операцию над полиномами" << std::endl;
        std::cout << "3. Вывести все полиномы" << std::endl;
        std::cout << "0. Выход" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1: {
            Polinom p;
            std::cout << "Введите полином:" << std::endl;
            std::cin >> p;
            polinoms.push_back(p);
            std::cout << "Полином добавлен." << std::endl;
            break;
        }
        case 2: {
            if (polinoms.size() < 2) {
                std::cout << "Необходимо ввести как минимум два полинома." << std::endl;
                break;
            }

            std::cout << "Выберите операцию:" << std::endl;
            std::cout << "1. Сложение полиномов" << std::endl;
            std::cout << "2. Вычитание полиномов" << std::endl;
            std::cout << "3. Умножение полинома на константу" << std::endl;
            std::cout << "4. Умножение полинома на моном" << std::endl;
            std::cout << "5. Умножение полиномов" << std::endl;

            int operation;
            std::cin >> operation;

            std::cout << "Введите номера полиномов (начиная с 0): ";
            int index1, index2;
            std::cin >> index1 >> index2;

            if (index1 < 0 || index1 >= polinoms.size() || index2 < 0 || index2 >= polinoms.size()) {
                std::cout << "Некорректные индексы полиномов." << std::endl;
                break;
            }

            switch (operation) {
            case 1: {
                Polinom sum = polinoms[index1] + polinoms[index2];
                std::cout << "Сумма полиномов: " << sum << std::endl;
                break;
            }
            case 2: {
                Polinom diff = polinoms[index1] - polinoms[index2];
                std::cout << "Разность полиномов: " << diff << std::endl;
                break;
            }
            case 3: {
                double constant;
                std::cout << "Введите константу: ";
                std::cin >> constant;
                Polinom scaled = polinoms[index1] * constant;
                std::cout << "Результат умножения на константу: " << scaled << std::endl;
                break;
            }
            case 4: {
                Monom mon;
                std::cout << "Введите моном для умножения: " << std::endl;
                std::cin >> mon;
                Polinom product = polinoms[index1] * mon;
                std::cout << "Результат умножения на моном: " << product << std::endl;
                break;
            }
           /* case 5: {
                Polinom product = polinoms[index1] * polinoms[index2];
                std::cout << "Результат умножения полиномов: " << product << std::endl;
                break;
            }*/
            default:
                std::cout << "Некорректный выбор операции." << std::endl;
            }
            break;
        }
        case 3: {
            if (polinoms.empty()) {
                std::cout << "Полиномы не введены." << std::endl;
            }
            else {
                for (size_t i = 0; i < polinoms.size(); ++i) {
                    std::cout << "Полином " << i << ": " << polinoms[i] << std::endl;
                }
            }
            break;
        }
        default:
            std::cout << "Некорректный выбор." << std::endl;
        }
    }

    return 0;
}